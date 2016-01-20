#pragma once

class Sprite;

class Hud
{
public:
	Hud(Sprite* p_pxSprite, float p_fX, float p_fY);
	~Hud();
	Sprite* GetSprite();
	float GetX();
	float GetY();

private:
	Sprite* m_pxSprite;
	float m_fX;
	float m_fY;
};