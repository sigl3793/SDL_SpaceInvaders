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
#include "CollisionManager.h"
#include "StateManager.h"
#include "MenuState.h"
#include <iostream>


GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayer = nullptr;
	m_pxShot = nullptr;

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

	SDL_Rect Waves[] =
	{
		{ 1,  32, 27, 24 }, // green
		{ 31, 32, 27, 24 }, // green
		{ 1,  2, 27, 27 }, // purple
		{ 31,  2, 27, 27 }, // purple
		{ 1, 62, 27, 27 }, // red
		{ 31, 62, 27, 27 }, // red
	};

	/*SDL_Rect Test[] =
	{
		{1,2,3,4,5,6,7,8,9,10},
		{11,12,13,14,15,16,17,18,19,20},
		{21,22,23,24,25,26,27,28,29,30},
		{31,32,33,34,35,36,37,38,39,40},
		{41,42,43,44,45,46,47,48,49,50},
		{51,52,53,54,55,56,57,58,59,60}
	};*/

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

			SDL_Rect& rect = Waves[(rand() % maxIndex) + minIndex];
			Invader* pxInvader = new Invader(
				m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invaders.bmp", rect.x, rect.y, rect.w, rect.h),
				-25.0f + i * 70.0f,
				50.0f + j * 50.0f);
			m_apxInvaders.push_back(pxInvader);
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

	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(p_fDeltaTime);
		}
		it++;
	}

	CheckCollision();
	if(m_xSystem.m_pxKeyboard->IsKeyDown(41))
	{
		return false;
	}
	else
		return true;

}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxPlayer->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
	m_xSystem.m_pxDrawManager->Draw(m_pxShot->GetSprite(), m_pxShot->GetX(), m_pxShot->GetY());
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

}

IState* GameState::NextState()
{
	return nullptr;
}

void GameState::CheckCollision()
{
	int iOverlapX = 0;
	int iOverlapY = 0;
	/*if (CollisionManager::Check(m_pxPlayer->GetCollider(), m_pxShot->GetCollider(), iOverlapX, iOverlapY))
	{
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
	}*/
	int m_iScreenWidth = 1024;
	int m_iScreenHeight = 768;
	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		if ((*it)->IsVisible())
		{
			if (CollisionManager::Check((*it)->GetCollider(), m_pxShot->GetCollider(), iOverlapX, iOverlapY))
			{
				(*it)->SetVisible(false);
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
			if ((*it)->GetX() <= 0)
			{
				(*it)->SetPosition(0, (*it)->GetY());
				(*it)->ReverseDirectionX();
			}

			if ((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w > m_iScreenWidth)
			{
				(*it)->SetPosition(m_iScreenWidth - (*it)->GetSprite()->GetRegion()->w, (*it)->GetY());
				(*it)->ReverseDirectionX();
			}

			if ((*it)->GetY() + (*it)->GetSprite()->GetRegion()->h > m_iScreenHeight)
			{
				SDL_Log("YOU LOSE");
			}
		}
		it++;
	}
}
