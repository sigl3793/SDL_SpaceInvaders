#include "stdafx.h"
#include "Engine.h"
#include "InputManager.h"
#include "StateManager.h"
#include "IState.h"
#include "Mouse.h"
#include "Shot.h"
#include "Keyboard.h"

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