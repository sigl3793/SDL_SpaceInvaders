#pragma once
#include "stdafx.h"
/*
Suggested structure for a potential future InputManager
Init will create objects needed and shutdown will delete them.
Update will handle all the events with SDL_PollEvent update the
mouse and keyboard objects accordingly.
Other functions will return appropriate data from the mouse and keyboard.*/

class Mouse;
class Keyboard;

class InputManager
{
	friend class Engine;
public:
	InputManager();
	~InputManager();
	//void Initialize();
	//void Shutdown();

	Keyboard* GetKeyboard();
	Mouse* GetMouse();
	void SetKeyboard(int key, bool state);
	void SetMouse(int button, bool state);
	/*int GetMouseX();
	int GetMouseY();
	bool IsMouseButtonDown(int p_iIndex);
	bool IsKeyDown(int p_iIndex);
	void Update(float p_fDeltaTime);*/
	

private:
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
	
	//std::map<int,bool> m_bKeyDown;
	//std::map<int, bool> m_bButtonDown;
};
