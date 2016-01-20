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
#include "InputManager.h"
#include "AudioManager.h"
#include "SoundClip.h"

WinState::WinState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_xMusic = nullptr;
	m_pxMenu = nullptr;
	m_pxSoundClip = nullptr;
}

WinState::~WinState()
{
	Mix_FreeMusic(m_xMusic);
	m_xMusic = nullptr;
}

void WinState::Enter()
{
	m_pxSoundClip = m_xSystem.m_pxAudioManager->CreateSound("../assets/win.wav");

	m_pxSoundClip->PlaySound();

	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Win.bmp", 0, 0, 1024, 768);
	SDL_Rect* xRect = xSprite->GetRegion();
	m_pxMenu = new Menu(m_xSystem.m_pxMouse, xSprite, 0, 0, m_xSystem.m_iScreenWidth, m_xSystem.m_iScreenHeight);
}

void WinState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxMenu->GetSprite());
	delete m_pxMenu;
	m_pxMenu = nullptr;

	m_xSystem.m_pxAudioManager->DestroySound("../assets/win.wav");
}

bool WinState::Update(float p_fDeltaTime)
{
	if (m_xSystem.m_pxInputManager->GetKeyboard()->IsKeyDown(41))
	{
		SDL_QUIT;
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