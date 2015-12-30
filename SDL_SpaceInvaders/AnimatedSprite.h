#pragma once

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	struct FrameData
	{
		//SDL_Texture* m_pxTexture;
		SDL_Rect m_xRegion;
		float m_fDuration;
	};

	AnimatedSprite(SDL_Texture* p_pxTexture);
	void AddFrame(int p_iX, int p_iY, int p_iWidth, int p_iHeight, float p_fDuration);
	void Update(float p_fDeltaTime);
private:
	std::vector<FrameData> m_axFrames;
	int m_iIndex;
	float m_fCurrentDuration;
};

// Vector is a list of all frames
// when we change index of what frame we are on
// we change what m_pxTexture is Pointing on.
// 8 frames över 0.5s
// 1-6 == 0.3s, 7-8 == 0.2s