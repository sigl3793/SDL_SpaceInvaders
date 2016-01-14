#pragma once

#include "IEntity.h"
class Mouse;

class EnemyShot : IEntity
{
public:
	EnemyShot(Mouse* p_pxMouse,Sprite* p_pxSprite, int p_iScreenWidth, int p_iScreenHeight);
	~EnemyShot();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	bool IsActive();
	EENTITYTYPE GetType();
	void Activate();
	void Deactivate();
	void SetPosition(float p_fX, float p_fY);
private:
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	float m_fSpeed;
	float m_fDirY;
	float m_fX;
	float m_fY;
	int m_iScreenWidth;
	int m_iScreenHeight;
	bool m_bVisible;
	bool m_bActive;
	Mouse* m_pxMouse;
};