#pragma once

class MusicClip
{
public:
	MusicClip(Mix_Music* p_pxMusic);
	~MusicClip();
	void PlayMusic(int p_iLoop);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();

private:
	Mix_Music* m_pxMusic;
};