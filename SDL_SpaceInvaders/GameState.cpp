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
#include "AudioManager.h"
#include "SoundClip.h"
#include "MusicClip.h"
#include "WinState.h"
#include <iostream>
#include "Engine.h"
#include "InputManager.h"
#include "Hud.h"


GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayer = nullptr;
	m_pxShot = nullptr;
	m_pxEnemyShot = nullptr;
	m_pxSoundClip1 = nullptr;
	m_pxSoundClip2 = nullptr;
	m_pxSoundClip3 = nullptr;
	m_pxHud1 = nullptr;
	m_pxHud2 = nullptr;
	m_pxHud3 = nullptr;
	Score = 0;
	Lives = 3;
}

GameState::~GameState()
{
}

void GameState::Enter()
{
	Mix_ResumeMusic();

	Sprite* xHud1 = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Lives.bmp", 0, 0, 228, 30);
	m_pxHud1 = new Hud(xHud1, 0, 0);

	Sprite* xHud2 = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Lives.bmp", 0, 0, 185, 30);
	m_pxHud2 = new Hud(xHud2, 0, 0);

	Sprite* xHud3 = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Lives.bmp", 0, 0, 145, 30);
	m_pxHud3 = new Hud(xHud3, 0, 0);

	m_pxSoundClip1 = m_xSystem.m_pxAudioManager->CreateSound("../assets/plop.wav");
	m_pxSoundClip2 = m_xSystem.m_pxAudioManager->CreateSound("../assets/hit.wav");
	m_pxSoundClip3 = m_xSystem.m_pxAudioManager->CreateSound("../assets/shot.wav");

	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/player.bmp", 0, 0, 60, 20);
	SDL_Rect* xRect = xSprite->GetRegion();
	int iHeight = xRect->h;
	m_pxPlayer = new Player(m_xSystem.m_pxInputManager,
		xSprite, 0,
		m_xSystem.m_iScreenHeight - 20 - iHeight,
		m_xSystem.m_iScreenWidth);

	m_pxShot = new Shot(m_xSystem.m_pxInputManager,
		m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invadersgammal.bmp", 73, 2, 3, 9),
		m_xSystem.m_iScreenWidth,
		m_xSystem.m_iScreenHeight);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			m_pxEnemyShot = new EnemyShot(m_xSystem.m_pxInputManager,
				m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invadersgammal.bmp", 73, 2, 3, 9),
				m_xSystem.m_iScreenWidth,
				m_xSystem.m_iScreenHeight);
			m_apxEnemyShot.push_back(m_pxEnemyShot);
		}
	}

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

			SDL_Rect& rect = Waves[(rand() % maxIndex) + minIndex];
			Invader* pxInvader = new Invader(
				m_xSystem.m_pxSpriteManager->CreateSprite("../assets/invaders.bmp", rect.x, rect.y, rect.w, rect.h),
				0.0f + i * 70.0f, //-25
				50.0f + j * 50.0f);
			m_apxInvaders.push_back(pxInvader);
		}
	}
}

void GameState::Exit()
{
	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it)->GetSprite());
		delete (*it);
		it++;
	}
	m_apxInvaders.clear();

	auto it2 = m_apxDefence.begin();
	while (it2 != m_apxDefence.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it2)->GetSprite());
		delete (*it2);
		it2++;
	}
	m_apxDefence.clear();

	auto it3 = m_apxEnemyShot.begin();
	while (it3 != m_apxEnemyShot.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it3)->GetSprite());
		delete (*it3);
		it3++;
	}

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxShot->GetSprite());
	delete m_pxShot;
	m_pxShot = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxPlayer->GetSprite());
	delete m_pxPlayer;
	m_pxPlayer = nullptr;

	m_xSystem.m_pxAudioManager->DestroySound("../assets/shot.wav");
	m_xSystem.m_pxAudioManager->DestroySound("../assets/hit.wav");
	m_xSystem.m_pxAudioManager->DestroySound("../assets/plop.wav");

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxHud3->GetSprite());
	delete m_pxHud3;
	m_pxHud3 = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxHud2->GetSprite());
	delete m_pxHud2;
	m_pxHud2 = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxHud1->GetSprite());
	delete m_pxHud1;
	m_pxHud1 = nullptr;

	Mix_HaltMusic();
}

bool GameState::Update(float p_fDeltaTime)
{
	m_pxPlayer->Update(p_fDeltaTime);

	m_pxShot->Update(p_fDeltaTime);
	if (m_pxShot->IsActive() == false)
	{
		m_pxShot->SetPosition(m_pxPlayer->GetX() + m_pxPlayer->GetSprite()->GetRegion()->w / 2 - m_pxShot->GetSprite()->GetRegion()->w / 2,
			m_pxPlayer->GetY() + m_pxPlayer->GetSprite()->GetRegion()->h / 2 - m_pxShot->GetSprite()->GetRegion()->h / 2);
	}
	if (m_pxShot->GetY() > m_xSystem.m_iScreenHeight)
	{
		m_pxShot->Deactivate();
		m_pxShot->SetPosition(m_pxPlayer->GetX() + m_pxPlayer->GetSprite()->GetRegion()->w / 2, m_pxPlayer->GetY());
	}

	auto it3 = m_apxEnemyShot.begin();
	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		if ((*it)->IsActive() && (*it)->IsVisible())
		{
			(*it)->Update(p_fDeltaTime);
			(*it3)->Update(p_fDeltaTime);
			if ((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w > m_xSystem.m_iScreenWidth || (*it)->GetX() <= 0)
			{
				for (auto it = m_apxInvaders.begin(); it != m_apxInvaders.end(); it++)
				{
					(*it)->ReverseDirectionX();
				}
			}
			if ((*it3)->IsActive() == false)
			{
				(*it3)->SetPosition((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w / 2 - (*it3)->GetSprite()->GetRegion()->w / 2,
					(*it)->GetY() - (*it)->GetSprite()->GetRegion()->h / 2 - (*it3)->GetSprite()->GetRegion()->h / 2);
			}
			if ((*it3)->GetY() > m_xSystem.m_iScreenHeight)
			{
				(*it3)->Deactivate();
				(*it3)->SetPosition((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w, (*it)->GetY() + (*it)->GetSprite()->GetRegion()->h);
			}
		}
		if ((*it)->GetY() + (*it)->GetSprite()->GetRegion()->h > m_xSystem.m_iScreenHeight)
		{
			return false;
		}
		it3++;
		it++;
	}

	if (Score == 6000)
	{
		return false;
	}
	if (Lives == 0)
	{
		return false;
	}

	CheckCollision();
	
	return true;
}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxPlayer->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());

	if (Lives == 3)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxHud1->GetSprite(), m_pxHud1->GetX(), m_pxHud1->GetY());
	}
	if (Lives == 2)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxHud2->GetSprite(), m_pxHud2->GetX(), m_pxHud2->GetY());
	}
	if (Lives == 1)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxHud3->GetSprite(), m_pxHud3->GetX(), m_pxHud3->GetY());
	}

	if (m_pxShot->IsActive() == true)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxShot->GetSprite(), m_pxShot->GetX(), m_pxShot->GetY());
	}

	auto it3 = m_apxEnemyShot.begin();
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
		if ((*it3)->IsActive() == true)
		{
			m_xSystem.m_pxDrawManager->Draw(
				(*it3)->GetSprite(),
				(*it3)->GetX(),
				(*it3)->GetY()
				);
		}
		it++;
		it3++;
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
					m_pxSoundClip1->PlaySound();
					std::cout << "Score:" << Score << std::endl;
				}
				else
				{
					m_pxShot->SetPosition(m_pxShot->GetX(), m_pxShot->GetY() - iOverlapY);
					m_pxShot->Deactivate();
					Score += 100;
					m_pxSoundClip1->PlaySound();
					std::cout << "Score:" << Score << std::endl;
				}
			}

			if (Score == 1000)
			{
				(*it)->IncreaseSpeed() == true;
			}

			if (Score == 2500)
			{
				(*it)->IncreaseSpeedAgain() == true;
			}
		}
		it++;
	}

	auto it2 = m_apxDefence.begin();
	while (it2 != m_apxDefence.end())
	{
		auto it5 = m_apxEnemyShot.begin();
		if ((*it2)->IsVisible())
		{
			if (CollisionManager::Check((*it2)->GetCollider(), m_pxShot->GetCollider(), iOverlapX, iOverlapY))
			{
				(*it2)->SetVisible(false);
				if (abs(iOverlapX) > abs(iOverlapY))
				{
					m_pxShot->SetPosition(m_pxShot->GetX() - iOverlapX, m_pxShot->GetY());
					m_pxSoundClip2->PlaySound();
					m_pxShot->Deactivate();
				}
				else
				{
					m_pxShot->SetPosition(m_pxShot->GetX(), m_pxShot->GetY() - iOverlapY);
					m_pxSoundClip2->PlaySound();
					m_pxShot->Deactivate();
				}
			}
		}
		while (it5 != m_apxEnemyShot.end())
		{
			if (CollisionManager::Check((*it2)->GetCollider(), (*it5)->GetCollider(), iOverlapX, iOverlapY))
			{
				if ((*it2)->IsVisible())
				{
					if (abs(iOverlapX) > abs(iOverlapY))
					{
						(*it5)->Deactivate();
						m_pxSoundClip2->PlaySound();
						(*it2)->SetVisible(false);
					}
					else
					{
						(*it5)->Deactivate();
						m_pxSoundClip2->PlaySound();
						(*it2)->SetVisible(false);
					}
				}
			}
			it5++;
		}
		it2++;
	}


	auto it3 = m_apxEnemyShot.begin();
	while (it3 != m_apxEnemyShot.end())
	{
		if (CollisionManager::Check((*it3)->GetCollider(), m_pxPlayer->GetCollider(), iOverlapX, iOverlapY))
		{
			if (abs(iOverlapX) > abs(iOverlapY))
			{
				(*it3)->Deactivate();
				Lives -= 1;
			}
			else
			{
				(*it3)->Deactivate();
				Lives -= 1;
			}
		}
		it3++;
	}
}
