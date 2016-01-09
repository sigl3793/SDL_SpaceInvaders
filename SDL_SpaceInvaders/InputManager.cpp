#include "stdafx.h"
#include "Engine.h"
#include "InputManager.h"
#include "StateManager.h"
#include "IState.h"
#include "Mouse.h"
#include "Shot.h"
#include "Keyboard.h"
#include <iostream>

InputManager::InputManager()
{
	// Kolla vilken state som är aktiv och uppdatera vilka knappar som gör vad
	m_pxMouse = nullptr;
	m_pxKeyboard = nullptr;
	
}


InputManager::~InputManager()
{

}

void InputManager::Initialize()
{
	m_pxMouse = new Mouse();

	m_pxKeyboard = new Keyboard();
}

void InputManager::Shutdown()
{
	delete m_pxKeyboard;
	m_pxKeyboard = nullptr;

	delete m_pxMouse;
	m_pxMouse = nullptr;
}

int InputManager::GetMouseX()
{
	return false;
}

int InputManager::GetMouseY()
{
	return false;
}

bool InputManager::IsMouseButtonDown(int p_iIndex) 
{ 
	
	return false;
}

bool InputManager::IsKeyDown(int p_iIndex) 
{ 
	return false; 
}

void InputManager::Update()
{
	SDL_Event xEvent;
	while (SDL_PollEvent(&xEvent))
	{

	}
}
