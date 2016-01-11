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
	m_pxMouse = nullptr;
	m_pxKeyboard = nullptr;
	m_pxInputManager = nullptr;
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
	m_pxMouse = new Mouse();

	m_pxKeyboard = new Keyboard();

	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxStateManager = new StateManager();

	m_pxInputManager = new InputManager();

	m_xSystem.m_iScreenWidth = SCREENWIDTH;
	m_xSystem.m_iScreenHeight = SCREEHEIGHT;
	m_xSystem.m_pxDrawManager = m_pxDrawManager;
	m_xSystem.m_pxSpriteManager = m_pxSpriteManager;
	m_xSystem.m_pxMouse = m_pxMouse;
	m_xSystem.m_pxKeyboard = m_pxKeyboard;

	m_pxStateManager->SetState(new GameState(m_xSystem));

	m_bRunning = true;

	return true;
}

void Engine::Shutdown()
{
	// The shutdown function will quit, delete and shutdown everything we have started up or created in initialize (In reverse order of creation)
	delete m_pxInputManager;
	m_pxInputManager = nullptr;

	delete m_pxStateManager;
	m_pxStateManager = nullptr;

	delete m_pxSpriteManager;
	m_pxSpriteManager = nullptr;

	delete m_pxKeyboard;
	m_pxKeyboard = nullptr;

	delete m_pxMouse;
	m_pxMouse = nullptr;

	// Shuts down the drawmanager before deleting the object and nulling the pointer.
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
			m_pxMouse->SetButton(xEvent.button.button, true);
		}
		else if (xEvent.type == SDL_MOUSEBUTTONUP)
		{
			m_pxMouse->SetButton(xEvent.button.button, false);
		}
		else if (xEvent.type == SDL_MOUSEMOTION)
		{
			m_pxMouse->SetPosition(xEvent.motion.x, xEvent.motion.y);
		}
		else if (xEvent.type == SDL_KEYDOWN)
		{
			m_pxKeyboard->SetKey(xEvent.button.button, true);
			//m_pxStateManager->SetState(new MenuState(m_xSystem));
		}
		else if (xEvent.type == SDL_KEYUP)
		{
			m_pxKeyboard->SetKey(xEvent.button.button, false);
		}
	}
}