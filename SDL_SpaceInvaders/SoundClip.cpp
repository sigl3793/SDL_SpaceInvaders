#include "stdafx.h"
#include "SoundClip.h"

SoundClip::SoundClip(Mix_Chunk* p_pxClip)
{
	m_pxClip = p_pxClip;
}

SoundClip::~SoundClip()
{
}

void SoundClip::PlaySound()
{
	Mix_PlayChannel(-1, m_pxClip, 0);
}
