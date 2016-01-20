#include "Menu.h"

Menu::Menu(Mouse* p_pxMouse, Sprite* p_pxSprite,float p_fX, float p_fY, int p_iScreenWidth, int p_iScreenHeight)
{
	m_pxMouse = p_pxMouse;
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;	
	m_iScreenWidth = p_iScreenWidth;
	m_iScreenHeight = p_iScreenHeight;
}

Menu::~Menu()
{
}

Sprite* Menu::GetSprite()
{
	return m_pxSprite;
}

float Menu::GetX()
{
	return m_fX;
}

float Menu::GetY()
{
	return m_fY;
}