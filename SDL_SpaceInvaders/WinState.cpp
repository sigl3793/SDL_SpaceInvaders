#include "stdafx.h"
#include "MenuState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Sprite.h"
#include <iostream> 
#include "StateManager.h"
#include "Menu.h"
#include "WinState.h"
#include "IState.h"

WinState::WinState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_xMusic = nullptr;
	m_pxMenu = nullptr;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
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

WinState::~WinState()
{
	Mix_FreeMusic(m_xMusic);
	m_xMusic = nullptr;
}

void WinState::Enter()
{
	Mix_PlayMusic(m_xMusic, 0);

	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Win.bmp", 0, 0, 1024, 768);
	SDL_Rect* xRect = xSprite->GetRegion();
	m_pxMenu = new Menu(m_xSystem.m_pxMouse, xSprite, 0, 0, m_xSystem.m_iScreenWidth, m_xSystem.m_iScreenHeight);
}

void WinState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxMenu->GetSprite());
	delete m_pxMenu;
	m_pxMenu = nullptr;
}

bool WinState::Update(float p_fDeltaTime)
{
	if (m_xSystem.m_pxKeyboard->IsKeyDown(41))
	{
		m_xSystem.m_pxKeyboard->SetKey(41, false);
		SDL_Quit();
	}
	return true;
}

void WinState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxMenu->GetSprite(), m_pxMenu->GetX(), m_pxMenu->GetY());
}

IState* WinState::NextState()
{
	return nullptr;
}