#pragma once

#include "stdafx.h"

class Mouse;
class Keyboard;

class InputManager
{
public:
	InputManager();
	~InputManager();
	Keyboard* GetKeyboard();
	Mouse* GetMouse();
	void SetKeyboard(int key, bool state);
	void SetMouse(int button, bool state);
	
private:
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
};
