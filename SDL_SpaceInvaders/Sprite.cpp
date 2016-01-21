#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Texture* p_pxTexture)
{
	m_pxTexture = p_pxTexture;
	m_xRegion.x = 0;
	m_xRegion.y = 0;
	m_xRegion.w = 0;
	m_xRegion.h = 0;
}

Sprite::Sprite(SDL_Texture* p_pxTexture, float p_fX, float p_fY, float p_fW, float p_fH)
{
	m_pxTexture = p_pxTexture;
	m_xRegion.x = p_fX;
	m_xRegion.y = p_fY;
	m_xRegion.w = p_fW;
	m_xRegion.h = p_fH;
}

Sprite::~Sprite()
{
}

SDL_Texture* Sprite::GetTexture()
{
	return m_pxTexture;
}

SDL_Rect* Sprite::GetRegion()
{
	return &m_xRegion;
}