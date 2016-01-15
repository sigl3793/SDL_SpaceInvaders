#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{

}

bool AudioManager::Initialize()
{
	Mix_Init(MIX_INIT_MP3);
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
		return false;
	}
	return true;
}

void AudioManager::Shutdown()
{
	auto it = m_apxSoundClips.begin();
	while (it != m_apxSoundClips.end())
	{
		delete (*it);
		it++;
	}
	m_apxSoundClips.clear();
	
	auto it2 = m_apxMusicClips.begin();
	while (it2 != m_apxMusicClips.end())
	{
		delete (*it2);
		it2++;
	}
	m_apxMusicClips.clear();
	
	Mix_CloseAudio();
	Mix_Quit();
}

SoundClip* AudioManager::CreateSound(const std::string& p_sFilepath)
{
	// First we try to find the texture in our std::map
	auto it = m_apxSoundCunks.find(p_sFilepath);
	if (it == m_apxSoundCunks.end())
	{
		// If we don't find the texture we need to load it and insert it in to our std::map so
		// that we may create pointers to the same texture for several chunks.
		Mix_Chunk* m_xChunk = Mix_LoadWAV(p_sFilepath.c_str());
		m_apxSoundCunks.insert(std::pair<std::string, Mix_Chunk*>(p_sFilepath, m_xChunk));
		it = m_apxSoundCunks.find(p_sFilepath);
	}
	SoundClip* xSound = new SoundClip(it->second);
	//m_apxSoundClips.push_back(xSound); ?
	return xSound;
}

MusicClip* AudioManager::CreateMusic(const std::string& p_sFilepath)
{
	auto it = m_apxMusicChunks.find(p_sFilepath);
	if (it == m_apxMusicChunks.end())
	{
		Mix_Music* m_xMusic = Mix_LoadMUS(p_sFilepath.c_str());
		m_apxMusicChunks.insert(std::pair<std::string, Mix_Music*>(p_sFilepath, m_xMusic));
		it = m_apxMusicChunks.find(p_sFilepath);
	}
	MusicClip* xMusic = new MusicClip((it->second));
	//m_apxMusicClips.push_back(xMusic); ?
	return xMusic;
}

void AudioManager::DestroySound(const std::string& p_sFilepath)
{
	auto it = m_apxSoundCunks.begin();
	while (it != m_apxSoundCunks.end())
	{
		if ((it->first) == p_sFilepath)
		{
			Mix_FreeChunk(it->second);
			m_apxSoundCunks.erase(it);
			return;
		}
		it++;
	}
}

void AudioManager::DestroyMusic(const std::string& p_sFilepath)
{
	auto it = m_apxMusicChunks.begin();
	while (it != m_apxMusicChunks.end())
	{
		if ((it->first) == p_sFilepath)
		{
			Mix_FreeMusic(it->second);
			m_apxMusicChunks.erase(it);
			return;
		}
		it++;
	}
}