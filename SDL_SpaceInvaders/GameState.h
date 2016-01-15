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
	EnemyShot* m_pxEnemyShot;
	std::vector<EnemyShot*> m_apxEnemyShot; // ???
	std::vector<Defence*> m_apxDefence;
	Defence* m_pxDefence;
	std::vector<Invader*> m_apxInvaders;
	Invader* m_pxInvader;
	Mix_Chunk* m_xPlopSound;
	Mix_Music* m_xMusic;
	int Score;

	SoundClip* m_pxSoundClip;
	AudioManager* m_pxAudioManager;
};
