#pragma once

#include "IState.h"
class Player;
class Invader;
class Shot;
class Defence;
class AnimatedSprite;

class GameState : public IState
{
public:
	GameState(System& p_xSystem);
	~GameState();
	void Enter();
	void Exit();
	bool Update(float p_fDeltaTime);
	void Draw();
	IState* NextState();
private:
	void CheckCollision();
	System m_xSystem;
	Player* m_pxPlayer;
	Shot* m_pxShot;
	std::vector<Defence*> m_apxDefence;
	Defence* m_pxDefence;
	std::vector<Invader*> m_apxInvaders;
	Mix_Chunk* m_xPlopSound;
	Mix_Music* m_xMusic;
	int Score;
};
