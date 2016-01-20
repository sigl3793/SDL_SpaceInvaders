#pragma once

class SoundClip
{
public:
	SoundClip(Mix_Chunk* p_pxClip);
	~SoundClip();
	void PlaySound();

private:
	Mix_Chunk* m_pxClip;
	int m_iLastChannelPlayed;
};