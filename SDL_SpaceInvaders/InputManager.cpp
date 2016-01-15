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
	m_pxMouse = new Mouse;
	m_pxKeyboard = new Keyboard;
}


InputManager::~InputManager()
{
	delete m_pxKeyboard;
	m_pxKeyboard = nullptr;

	delete m_pxMouse;
	m_pxMouse = nullptr;
}

/*void InputManager::Initialize()
{

}

void InputManager::Shutdown()
{

}*/

Keyboard* InputManager::GetKeyboard()
{
	return m_pxKeyboard;
}

void InputManager::SetKeyboard(int key, bool state)
{
	m_pxKeyboard->SetKey(key, state);
}

Mouse* InputManager::GetMouse()
{
	return m_pxMouse;
}

void InputManager::SetMouse(int button, bool state)
{
	m_pxMouse->SetButton(button, state);
}
/*int InputManager::GetMouseX()
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

void InputManager::Update(float p_fDeltaTime)
{

}*/
