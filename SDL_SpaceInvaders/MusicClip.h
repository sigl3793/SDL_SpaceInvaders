#pragma once

#include "stdafx.h"

class MusicClip
{
public:
	MusicClip(Mix_Music* p_pxMusic);
	~MusicClip();
	void PlayMusic(int p_fLoop = -1);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
private:
	Mix_Music* m_pxMusic;
};