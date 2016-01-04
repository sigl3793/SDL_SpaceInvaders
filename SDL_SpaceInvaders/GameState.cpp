#include "stdafx.h"
#include "GameState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Mouse.h"
#include "Sprite.h"
#include "Player.h"
#include "Invader.h"
#include "CollisionManager.h"
#include "StateManager.h"
#include "MenuState.h"
#include <iostream>


GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayer = nullptr;

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
				0.0f + i * 70.0f,
				0.0f + j * 50.0f);
			//pxInvader->SetPosition(0.0f, 0.0f);
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

	auto it = m_apxInvaders.begin();
	while (it != m_apxInvaders.end())
	{
		if ((*it)->IsActive())
		{
			(*it)->Update(p_fDeltaTime);
		}
		it++;
	}
	/*if (m_pxBall->GetY() > m_xSystem.m_iScreenHeight)
	{
		m_pxBall->Deactivate();
		SDL_Log("Player lost a life");
	}*/

	CheckCollision();
	return true;
}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxPlayer->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
	
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

}
