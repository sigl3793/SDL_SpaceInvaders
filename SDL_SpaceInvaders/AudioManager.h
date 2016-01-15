#pragma once

#include "stdafx.h"
#include "SoundClip.h"
#include "MusicClip.h"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	void Shutdown();
	SoundClip* CreateSound(const std::string& p_sFilepath);
	MusicClip* CreateMusic(const std::string& p_sFilepath);
	void DestroySound(const std::string& p_sFilepath);
	void DestroyMusic(const std::string& p_sFilepath);
private:
	SoundClip* m_pxSoundClip;
	MusicClip* m_pxMusicClip;
	std::map<std::string, Mix_Chunk*> m_apxSoundCunks;
	std::map<std::string, Mix_Music*> m_apxMusicChunks;
	std::vector<SoundClip*> m_apxSoundClips;
	std::vector<MusicClip*> m_apxMusicClips;
	
};