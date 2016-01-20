#include "stdafx.h"
#include "MusicClip.h"

MusicClip::MusicClip(Mix_Music* p_pxMusic)
{
	m_pxMusic = p_pxMusic;
	int p_iLoop = -1;
}

MusicClip::~MusicClip()
{
}

void MusicClip::PlayMusic(int p_iLoop)
{
	Mix_PlayMusic(m_pxMusic, p_iLoop);
}

void MusicClip::StopMusic()
{
	Mix_HaltMusic();
}

void MusicClip::PauseMusic()
{
	Mix_PauseMusic();
}

void MusicClip::ResumeMusic()
{
	Mix_ResumeMusic();
}