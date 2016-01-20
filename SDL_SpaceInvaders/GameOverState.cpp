#include "stdafx.h"
#include "GameOverState.h"
#include "Menu.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "Sprite.h"
#include <iostream> 
#include "StateManager.h"
#include "MenuState.h"
#include "IState.h"

GameOverState::GameOverState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
}

GameOverState::~GameOverState()
{
}

void GameOverState::Enter()
{
	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/GameOver.bmp", 0, 0, 1024, 768);
	SDL_Rect* xRect = xSprite->GetRegion();
	m_pxMenu = new Menu(m_xSystem.m_pxMouse, xSprite, 0, 0, m_xSystem.m_iScreenWidth, m_xSystem.m_iScreenHeight);
}

void GameOverState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxMenu->GetSprite());
	delete m_pxMenu;
	m_pxMenu = nullptr;
}

bool GameOverState::Update(float p_fDeltaTime)
{
	if (m_xSystem.m_pxInputManager->GetKeyboard()->IsKeyDown(41))
	{
		SDL_Quit();
		m_xSystem.m_pxInputManager->GetKeyboard()->SetKey(41, false);
	}
	if (m_xSystem.m_pxInputManager->GetKeyboard()->IsKeyDown(40))
	{
		return false;
		m_xSystem.m_pxInputManager->GetKeyboard()->SetKey(40, false);
	}
	return true;
}

void GameOverState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxMenu->GetSprite(), m_pxMenu->GetX(), m_pxMenu->GetY());
}

IState* GameOverState::NextState()
{
	return (new MenuState(m_xSystem));
}
