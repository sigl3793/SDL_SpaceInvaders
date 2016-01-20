#pragma once

class SpriteManager;
class DrawManager;
class Mouse;
class Keyboard;
class AudioManager;
class InputManager;

struct System
{
	int m_iScreenWidth;
	int m_iScreenHeight;
	SpriteManager* m_pxSpriteManager;
	DrawManager* m_pxDrawManager;
	Mouse* m_pxMouse;
	Keyboard* m_pxKeyboard;
	AudioManager* m_pxAudioManager;
	InputManager* m_pxInputManager;
};

class IState
{
public:
	virtual ~IState() {};
	virtual void Enter() {};
	virtual bool Update(float p_fDeltaTime) = 0;
	virtual void Exit() {};
	virtual void Draw() = 0;
	virtual IState* NextState() = 0;

};