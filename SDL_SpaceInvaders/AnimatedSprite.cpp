#include "stdafx.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Texture* p_pxTexture) : Sprite(p_pxTexture) // överlagrad konstruktor
{
	// create info on the 4 frames
	m_iIndex = 0;
	m_fCurrentDuration = 0.f;
	//m_pxTexture < -ska vi alltid använda
}

void AnimatedSprite::AddFrame(int p_iX, int p_iY, int p_iWidth, int p_iHeight, float p_fDuration)
{
	FrameData data;
	data.m_xRegion.x = p_iX;
	data.m_xRegion.y = p_iY;
	data.m_xRegion.w = p_iWidth;
	data.m_xRegion.h = p_iHeight;
	data.m_fDuration = p_fDuration;
	m_axFrames.push_back(data);
}

void AnimatedSprite::Update(float p_fDeltaTime)
{
	m_fCurrentDuration += p_fDeltaTime;
	if (m_fCurrentDuration >= m_axFrames[m_iIndex].m_fDuration) // we need to change frame
	{
		// lets assume we have 4 frames == that means index 0,1,2,3
		// (   3    <    4-1   ) == false goto else clause
		//							(not that kind of clause)
		if (m_iIndex < m_axFrames.size()-1)
		{
			m_iIndex++;
		}
		else
		{
			m_iIndex = 0;
		}
		//m_pxTexture = m_axFrames[m_iIndex].m_pxTexture;
		m_xRegion = m_axFrames[m_iIndex].m_xRegion;
		m_fCurrentDuration = 0.0f;
	}

	// check out current duration versus the current
	// frames duration, if the duration has passed
	// over the frame duration then switch to the next frame
	// if we reach the end frame of the list, then start from index 0 again

	// increase the current duration

	// m_axFrames[0] -> m_axFrames[amount of frames]
}