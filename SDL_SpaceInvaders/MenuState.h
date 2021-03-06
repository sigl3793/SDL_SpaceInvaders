#pragma once

#include "IState.h"
#include "Menu.h"
#include "StateManager.h"

class StateManager;
class MusicClip;
class AudioManager;

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
	Mix_Music* m_pxMusic;
	Menu* m_pxMenu;
	StateManager* m_pxStateManager;
	AudioManager* m_pxAudioManager;
};