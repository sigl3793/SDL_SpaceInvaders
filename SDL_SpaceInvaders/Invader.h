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
	void SetVisible(bool p_bValue);
	bool IsActive();
	void Deactivate();
	void SetDirectionX(float p_fDirX);
	void SetDirectionY(float p_fDirY);
	void SetPosition(float p_fX, float p_fY);
	void ReverseDirectionX();
	bool IncreaseSpeed();
	bool IncreaseSpeedAgain();

private:
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	int m_iScreenWidth;
	int m_iScreenHeight;
	float m_fX;
	float m_fY;
	float m_fDirX;
	float m_fDirY;
	float m_fSpeed;
	float m_fISpeed;
	bool m_bVisible;
	bool m_bActive;
	bool m_bIncrease;
	bool m_bIncreaseAgain;
	
};
