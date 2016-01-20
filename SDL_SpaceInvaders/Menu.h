#pragma once

class Mouse;
class Sprite;

class Menu
{
public:
	Menu(Mouse* p_pxMouse, Sprite* p_pxSprite,float p_fX, float p_fY, int p_iScreenWidth, int p_iScreenHeight);
	~Menu();
	Sprite* GetSprite();
	float GetX();
	float GetY();

private:
	Sprite* m_pxSprite;
	Mouse* m_pxMouse;
	int m_iScreenWidth;
	int m_iScreenHeight;
	float m_fX;
	float m_fY;

};