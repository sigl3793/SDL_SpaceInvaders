#include "stdafx.h"
#include "Engine.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "Sprite.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "GameState.h"
#include "MenuState.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "IState.h"
#include <iostream>
#include <ctime>

const int SCREENWIDTH = 1024;
const int SCREEHEIGHT = 768;

Engine::Engine()
{
	m_bRunning = false;
	m_pxDrawManager = nullptr;
	m_pxSpriteManager = nullptr;
	m_pxStateManager = nullptr;
	m_pxInputManager = nullptr;
	m_pxAudioManager = nullptr;
}

Engine::~Engine()
{
}


bool Engine::Initialize()
{
	// The initialize function will intialize libraries the program depends on and all manager we will create.

	srand((unsigned int)time(0)); //Initializes a random seed for when we will be using rand() in the future

								  // Initializes the SDL library
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	// Creates a new DrawManager and calls Initialize with width / height parameters.
	m_pxDrawManager = new DrawManager();
	if (m_pxDrawManager->Initialize(SCREENWIDTH, SCREEHEIGHT) == false)
	{
		return false;
	}

	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxStateManager = new StateManager();

	m_pxInputManager = new InputManager();

	m_pxAudioManager = new AudioManager();

	m_xSystem.m_iScreenWidth = SCREENWIDTH;
	m_xSystem.m_iScreenHeight = SCREEHEIGHT;
	m_xSystem.m_pxDrawManager = m_pxDrawManager;
	m_xSystem.m_pxSpriteManager = m_pxSpriteManager;
	m_xSystem.m_pxMouse = m_pxMouse;
	m_xSystem.m_pxKeyboard = m_pxKeyboard;
	m_xSystem.m_pxAudioManager = m_pxAudioManager;
	m_xSystem.m_pxInputManager = m_pxInputManager;

	m_pxStateManager->SetState(new MenuState(m_xSystem));

	m_bRunning = true;

	return true;
}

void Engine::Shutdown()
{
	// The shutdown function will quit, delete and shutdown everything we have started up or created in initialize (In reverse order of creation)
	m_pxAudioManager->Shutdown();
	delete m_pxAudioManager;
	m_pxAudioManager = nullptr;
	
	delete m_pxInputManager;
	m_pxInputManager = nullptr;

	delete m_pxStateManager;
	m_pxStateManager = nullptr;

	delete m_pxSpriteManager;
	m_pxSpriteManager = nullptr;

	m_pxDrawManager->Shutdown();
	delete m_pxDrawManager;
	m_pxDrawManager = nullptr;

	SDL_Quit();
}

void Engine::Update()
{
	// Our engines core loop
	while (m_bRunning)
	{
		HandleEvents();
		m_pxDrawManager->Clear();
		m_pxAudioManager->Initialize();
		m_pxInputManager;
		if (m_pxStateManager->Update() == false)
		{
			m_bRunning = false;
		}
		m_pxStateManager->Draw();
		m_pxDrawManager->Present();
		SDL_Delay(10);
	}
}

void Engine::HandleEvents()
{
	SDL_Event xEvent;
	while (SDL_PollEvent(&xEvent))
	{
		if (xEvent.type == SDL_QUIT)
		{
			m_bRunning = false;
		}
		else if (xEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			m_pxInputManager->GetMouse()->SetButton(xEvent.button.button, true);
		}
		else if (xEvent.type == SDL_MOUSEBUTTONUP)
		{
			m_pxInputManager->GetMouse()->SetButton(xEvent.button.button, false);
		}
		else if (xEvent.type == SDL_MOUSEMOTION)
		{
			m_pxInputManager->GetMouse()->SetPosition(xEvent.motion.x, xEvent.motion.y);
		}
		else if (xEvent.type == SDL_KEYDOWN)
		{
			m_pxInputManager->GetKeyboard()->SetKey(xEvent.button.button, true);
		}
		else if (xEvent.type == SDL_KEYUP)
		{
			m_pxInputManager->GetKeyboard()->SetKey(xEvent.button.button, false);
		}
	}
}