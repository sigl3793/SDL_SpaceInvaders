#pragma once

#include "IState.h"
#include "Menu.h"
#include "StateManager.h"

class StateManager;

class GameOverState : public IState
{
public:
	GameOverState(System& p_xSystem);
	~GameOverState();
	void Enter();
	void Exit();
	bool Update(float p_fDeltaTime);
	void Draw();
	IState* NextState();

private:
	System m_xSystem;
	Mix_Music* m_xMusic;
	Menu* m_pxMenu;
	StateManager* m_pxStateManager;
};