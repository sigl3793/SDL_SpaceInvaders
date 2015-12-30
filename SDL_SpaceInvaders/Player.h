#pragma once

#include "IEntity.h"
class Mouse;

class Player : public IEntity
{
public:
	Player(Mouse* p_pxMouse, Sprite* p_pxSprite,
		float p_fX, float p_fY, int p_iScreenWidth);
	~Player();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EENTITYTYPE GetType();

	//void Shoot(bool p_bShoot);

private:
	Player() {};
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	Mouse* m_pxMouse;
	float m_fX;
	float m_fY;
	int m_iScreenWidth;
	bool m_bVisible;

	//bool m_bShoot;
};