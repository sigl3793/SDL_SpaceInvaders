#include "stdafx.h"
#include "GameState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Player.h"
#include "Invader.h"
#include "Shot.h"
#include "EnemyShot.h"
#include "Defence.h"
#include "CollisionManager.h"
#include "StateManager.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "WinState.h"
#include <iostream>
#include "Engine.h"


GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayer = nullptr;
	m_pxShot = nullptr;
	m_pxEnemyShot = nullptr;
	Score = 0;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
	}

	m_xPlopSound = Mix_LoadWAV("../assets/plop.wav");
	if (m_xPlopSound == nullptr)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
	}

	m_xMusic = Mix_LoadMUS("../assets/batmetal.wav");
	if (m_xMusic == nullptr)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
	}
}

GameState::~GameState()
{
	Mix_FreeChunk(m_xPlopSound);
	m_xPlopSound = nullptr;

	Mix_FreeMusic(m_xMusic);
	m_xMusic = nullptr;
}

void GameState::Enter()
{
	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/player.bmp", 0, 0, 60, 20);
	SDL_Rect* xRect = xSprite->GetRegion();
	int iHeight = xRect->h;
	m_pxPlayer = new Player(m_xSystem.m_pxMouse,
		xSprite, 0,
		m_xSystem.m_iScreenHeight - 20 - iHeight,
		m_xSystem.m_iScreenWidth);

	m_pxShot = new Shot(m_xSystem.m_pxMouse,
		m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invadersgammal.bmp", 73, 2, 3, 9),
		m_xSystem.m_iScreenWidth,
		m_xSystem.m_iScreenHeight);

	m_pxEnemyShot = new EnemyShot(m_xSystem.m_pxMouse,
		m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invadersgammal.bmp", 73, 2, 3, 9),
		m_xSystem.m_iScreenWidth,
		m_xSystem.m_iScreenHeight);

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int x = 0; x < 3; x++)
			{
				m_pxDefence = new Defence(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 0, 0, 16, 16),
					100 + (i*125.0f) + x*16,
					600 + j * 16.0f);
				m_apxDefence.push_back(m_pxDefence);
			}
		}
	}


	SDL_Rect Waves[] =
	{
		{ 1,  32, 27, 24 }, // green
		{ 31, 32, 27, 24 }, // green
		{ 1,  2, 27, 27 }, // purple
		{ 31,  2, 27, 27 }, // purple
		{ 1, 62, 27, 27 }, // red
		{ 31, 62, 27, 27 }, // red
	};

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			int minIndex = 0;
			int maxIndex = 6;
			if (j >= 0)
			{
				minIndex = 0;
				maxIndex = 2;
			}
			if (j >= 2)
			{
				minIndex = 2;
				maxIndex = 2;
			}
			if (j >= 4)
			{
				minIndex = 4;
				maxIndex = 2;
			}
			// Invader*
			SDL_Rect& rect = Waves[(rand() % maxIndex) + minIndex];
			m_pxInvader = new Invader(
				m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invaders.bmp", rect.x, rect.y, rect.w, rect.h),
				0.0f + i * 70.0f, //-25
				50.0f + j * 50.0f);
			m_apxInvaders.push_back(m_pxInvader);
		}
	}

	//Mix_PlayMusic(m_xMusic, -1);
}

void GameState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxPlayer->GetSprite());
	delete m_pxPlayer;
	m_pxPlayer = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxShot->GetSprite());
	delete m_pxShot;
	m_pxShot = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxEnemyShot->GetSprite());
	delete m_pxEnemyShot;
	m_pxEnemyShot = nullptr;

	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it)->GetSprite());
		delete (*it);
		it++;
	}
	m_apxInvaders.clear();
}

bool GameState::Update(float p_fDeltaTime)
{
	m_pxPlayer->Update(p_fDeltaTime);

	m_pxShot->Update(p_fDeltaTime);
	if (m_pxShot->IsActive() == false)
	{
		m_pxShot->SetPosition(m_pxPlayer->GetX() + m_pxPlayer->GetSprite()->GetRegion()->w / 2 - m_pxShot->GetSprite()->GetRegion()->w / 2,
			m_pxPlayer->GetY() - m_pxPlayer->GetSprite()->GetRegion()->h / 2 - m_pxShot->GetSprite()->GetRegion()->h / 2 + 15);
	}
	if (m_pxShot->GetY() > m_xSystem.m_iScreenHeight)
	{
		m_pxShot->Deactivate();
	}

	m_pxEnemyShot->Update(p_fDeltaTime);
	if (m_pxEnemyShot->IsActive() == false)
	{
		m_pxEnemyShot->SetPosition(m_pxInvader->GetX() + m_pxInvader->GetSprite()->GetRegion()->w / 2 - m_pxEnemyShot->GetSprite()->GetRegion()->w / 2,
			m_pxInvader->GetY() - m_pxInvader->GetSprite()->GetRegion()->h / 2 - m_pxEnemyShot->GetSprite()->GetRegion()->h / 2);
	}
	if (m_pxEnemyShot->GetY() > m_xSystem.m_iScreenHeight)
	{
		m_pxEnemyShot->Deactivate();
	}

	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(p_fDeltaTime);
			if ((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w > m_xSystem.m_iScreenWidth || (*it)->GetX() <= 0)
			{
				for (auto it2 = m_apxInvaders.begin(); it2 != m_apxInvaders.end(); it2++)
				{
					(*it2)->ReverseDirectionX();
				}
			}
			if ((*it)->GetY() + (*it)->GetSprite()->GetRegion()->h >  m_xSystem.m_iScreenHeight)
			{
				return false;
			}
			else if (Score == 6000)
			{
				return false;
			}
		}
		it++;
	}

	CheckCollision();
	
	return true;
}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxPlayer->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
	
	if (m_pxShot->IsActive() == true)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxShot->GetSprite(), m_pxShot->GetX(), m_pxShot->GetY());
	}

	if (m_pxEnemyShot->IsActive() == true)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxEnemyShot->GetSprite(), m_pxEnemyShot->GetX(), m_pxEnemyShot->GetY());
	}

	
	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		if ((*it)->IsVisible())
		{
			m_xSystem.m_pxDrawManager->Draw(
				(*it)->GetSprite(),
				(*it)->GetX(),
				(*it)->GetY()
				);
		}
		it++;
	}

	auto it2 = m_apxDefence.begin();
	while (it2 != m_apxDefence.end())
	{
		if ((*it2)->IsVisible())
		{
			m_xSystem.m_pxDrawManager->Draw(
				(*it2)->GetSprite(),
				(*it2)->GetX(),
				(*it2)->GetY()
				);
		}
		it2++;
	}
}

IState* GameState::NextState()
{
	if (Score == 6000)
	{
		return (new WinState(m_xSystem));
	}
	else
		return (new GameOverState(m_xSystem));
}

void GameState::CheckCollision()
{
	int iOverlapX = 0;
	int iOverlapY = 0;

	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		//[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,58,59]
		if ((*it)->IsVisible())
		{
			if (CollisionManager::Check((*it)->GetCollider(), m_pxShot->GetCollider(), iOverlapX, iOverlapY))
			{
				(*it)->SetVisible(false);
				if (abs(iOverlapX) > abs(iOverlapY))
				{
					m_pxShot->SetPosition(m_pxShot->GetX() - iOverlapX, m_pxShot->GetY());
					m_pxShot->Deactivate();
					Score += 100;
					std::cout << "Score:" << Score << std::endl;
				}
				else
				{
					m_pxShot->SetPosition(m_pxShot->GetX(), m_pxShot->GetY() - iOverlapY);
					m_pxShot->Deactivate();
					Score += 100;
					std::cout << "Score:" << Score << std::endl;
				}
			}

			if (Score == 200)
			{
				(*it)->IncreaseSpeed() == true;

			}
			/*if (Score >= 6000)
			{
				std::cout << "YOU WIN" << std::endl;
				//SDL_QUIT?????
			}
			if ((*it)->GetX() <= 0)
			{
				(*it)->SetPosition(0, (*it)->GetY());
				(*it)->ReverseDirectionX();
			}
	
			if ((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w > m_xSystem.m_iScreenWidth)
			{
				(*it)->SetPosition(m_xSystem.m_iScreenWidth - (*it)->GetSprite()->GetRegion()->w, (*it)->GetY());
				(*it)->ReverseDirectionX();
			}*/
			
			if ((*it)->GetY() + (*it)->GetSprite()->GetRegion()->h >  m_xSystem.m_iScreenHeight)
			{
				SDL_Log("YOU LOSE");
			}
		}
		it++;
	}

	auto it2 = m_apxDefence.begin();
	while (it2 != m_apxDefence.end())
	{
		if ((*it2)->IsVisible())
		{
			if (CollisionManager::Check((*it2)->GetCollider(), m_pxShot->GetCollider(), iOverlapX, iOverlapY))
			{
				(*it2)->SetVisible(false);
				if (abs(iOverlapX) > abs(iOverlapY))
				{
					m_pxShot->SetPosition(m_pxShot->GetX() - iOverlapX, m_pxShot->GetY());
					m_pxShot->Deactivate();
				}
				else
				{
					m_pxShot->SetPosition(m_pxShot->GetX(), m_pxShot->GetY() - iOverlapY);
					m_pxShot->Deactivate();
				}
			}
		}
		it2++;
	}
}
