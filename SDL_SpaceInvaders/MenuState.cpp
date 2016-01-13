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
#include "GameState.h"
#include "IState.h"

MenuState::MenuState(System& p_xSystem)
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

MenuState::~MenuState()
{
	Mix_FreeMusic(m_xMusic);
	m_xMusic = nullptr;
}

void MenuState::Enter()
{
	Mix_PlayMusic(m_xMusic, 0);
	
	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/menu.bmp", 0, 0,1024,768);
	SDL_Rect* xRect = xSprite->GetRegion();
	m_pxMenu = new Menu(m_xSystem.m_pxMouse, xSprite,0,0, m_xSystem.m_iScreenWidth, m_xSystem.m_iScreenHeight);
}

void MenuState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxMenu->GetSprite());
	delete m_pxMenu;
	m_pxMenu = nullptr;
}

bool MenuState::Update(float p_fDeltaTime)
{
	if (m_xSystem.m_pxKeyboard->IsKeyDown(41))
	{
		m_xSystem.m_pxKeyboard->SetKey(41, false);
		SDL_Quit();
	}
	if (m_xSystem.m_pxKeyboard->IsKeyDown(40))
	{
		m_xSystem.m_pxKeyboard->SetKey(40, false);
		return false;
	}
	else
		return true;
}

void MenuState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxMenu->GetSprite(), m_pxMenu->GetX(), m_pxMenu->GetY());
}

IState* MenuState::NextState()
{
	return (new GameState(m_xSystem));
	//return nullptr;
}

