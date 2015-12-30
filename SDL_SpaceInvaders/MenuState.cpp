#include "stdafx.h"
#include "MenuState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Mouse.h"
#include "Sprite.h"
#include <iostream>
#include "StateManager.h"

MenuState::MenuState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_xMusic = nullptr;

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
}

void MenuState::Exit()
{

}

bool MenuState::Update(float p_fDeltaTime)
{
	return true;
}

void MenuState::Draw()
{

}

IState* MenuState::NextState()
{
	return nullptr;
}

