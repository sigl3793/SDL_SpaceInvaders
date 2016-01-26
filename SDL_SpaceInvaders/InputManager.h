#pragma once

#include "stdafx.h"
#include <glm.hpp>
//#include <unordered_map>

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
	void SetMouseCoords(float x, float y);
	
private:
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
	glm::vec2 _mouseCoords;
};