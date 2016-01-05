#include "stdafx.h"
#include "Engine.h"
#include "InputManager.h"
#include "Mouse.h"
#include "Keyboard.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{

}

void InputManager::Initialize()
{

}

void InputManager::Shutdown()
{

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
