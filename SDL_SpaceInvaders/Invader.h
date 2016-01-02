#pragma once

#include "IEntity.h"

class Invader : public IEntity
{
public:
	Invader(Sprite* p_pxSprite, float p_fX, float p_fY);
	~Invader();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EENTITYTYPE GetType();
	//char Waves[5];

	void SetVisible(bool p_bValue);

	bool IsActive();
	//void Activate();
	void Deactivate();
	void SetDirectionX(float p_fDirX);
	//void SetPosition(float p_fX, float p_fY);
	void ReverseDirectionX();
private:
	//AnimatedSprite* m_pxAnimatedSprite;
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	float m_fX;
	float m_fY;
	int m_iScreenWidth;
	int m_iScreenHeight;
	bool m_bVisible;
	
	bool m_bActive;
	float m_fSpeed;
	float m_fDirX;
	float m_fDirY;
};
