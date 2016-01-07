#pragma once
#include "IState.h"

class DrawManager;
class SpriteManager;
class StateManager;
class Mouse;
class Keyboard;

class Engine
{
public:
	Engine();
	~Engine();

	/**
	* Initializes SDL and creates all Managers
	*/
	bool Initialize();

	/**
	* Quits SDL and deletes all Managers
	*/
	void Shutdown();

	/**
	* The Engines update loop
	*/
	void Update();
	void HandleEvents();

private:
	bool m_bRunning;
	System m_xSystem;
	DrawManager* m_pxDrawManager;
	SpriteManager* m_pxSpriteManager;
	StateManager* m_pxStateManager;
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
	int states;

};
