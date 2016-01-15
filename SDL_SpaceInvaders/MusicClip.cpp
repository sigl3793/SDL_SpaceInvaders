#include "stdafx.h"
#include "MusicClip.h"

MusicClip::MusicClip(Mix_Music* pxMusic) : m_pxMusic(pxMusic)
{

}

MusicClip::~MusicClip()
{

}

void MusicClip::PlayMusic(int p_fLoop)
{
	Mix_PlayMusic(m_pxMusic, p_fLoop);
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