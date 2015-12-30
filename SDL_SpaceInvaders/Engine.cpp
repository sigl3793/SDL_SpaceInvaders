#include "stdafx.h"
#include "Engine.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "Sprite.h"
#include "Mouse.h"
#include "GameState.h"
#include "MenuState.h"
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

	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxStateManager = new StateManager();

	System system;
	system.m_iScreenWidth = SCREENWIDTH;
	system.m_iScreenHeight = SCREEHEIGHT;
	system.m_pxDrawManager = m_pxDrawManager;
	system.m_pxSpriteManager = m_pxSpriteManager;
	system.m_pxMouse = m_pxMouse;

	m_pxStateManager->SetState(new GameState(system));
	//m_pxStateManager->SetState(new MenuState(system));
	// Har jag med den över så körs endast menustate

	m_bRunning = true;

	return true;
}

void Engine::Shutdown()
{
	// The shutdown function will quit, delete and shutdown everything we have started up or created in initialize (In reverse order of creation)
	delete m_pxStateManager;
	m_pxStateManager = nullptr;

	delete m_pxSpriteManager;
	m_pxSpriteManager = nullptr;

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
		else if (xEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			// Vill lägga till så att det byter till menu men osäker om det är här man gör det
		}
	}
}