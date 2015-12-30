#pragma once

#include "IState.h"
class Mouse;

class MenuState : public IState
{
public:
	MenuState(System& p_xSystem);
	~MenuState();
	void Enter();
	void Exit();
	bool Update(float p_fDeltaTime);
	void Draw();
	IState* NextState();
private:
	System m_xSystem;
	Mouse* m_pxMouse;
	Mix_Music* m_xMusic;
	MenuState* m_pxMenuState;

};