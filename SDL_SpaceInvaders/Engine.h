#pragma once

#include "IState.h"

class DrawManager;
class SpriteManager;
class StateManager;
class Mouse;
class Keyboard;
class InputManager;
class AudioManager;

class Engine
{
public:
	Engine();
	~Engine();
	bool Initialize();
	void Shutdown();
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
	InputManager* m_pxInputManager;
	AudioManager* m_pxAudioManager;
};
