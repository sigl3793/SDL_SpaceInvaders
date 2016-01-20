#include "stdafx.h"
#include "Hud.h"

Hud::Hud(Sprite* p_pxSprite, float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
}

Hud::~Hud()
{
}

Sprite* Hud::GetSprite()
{
	return m_pxSprite;
}

float Hud::GetX()
{
	return m_fX;
}

float Hud::GetY()
{
	return m_fY;
}