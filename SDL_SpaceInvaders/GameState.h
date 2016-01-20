#pragma once

#include "IState.h"

class Player;
class Invader;
class Shot;
class EnemyShot;
class Defence;
class AnimatedSprite;
class AudioManager;
class SoundClip;
class MusicClip;
class Hud;
class Sprite;

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
	int Score;
	int Lives;
	void CheckCollision();
	System m_xSystem;
	Player* m_pxPlayer;
	Shot* m_pxShot;
	EnemyShot* m_pxEnemyShot;
	Defence* m_pxDefence;
	Invader* m_pxInvader;
	std::vector<EnemyShot*> m_apxEnemyShot;
	std::vector<Defence*> m_apxDefence;
	std::vector<Invader*> m_apxInvaders;
	SoundClip* m_pxSoundClip1;
	SoundClip* m_pxSoundClip2;
	SoundClip* m_pxSoundClip3;
	Hud* m_pxHud1;
	Hud* m_pxHud2;
	Hud* m_pxHud3;
};
