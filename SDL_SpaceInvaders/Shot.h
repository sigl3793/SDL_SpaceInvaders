#pragma once

#include "IEntity.h"
class Mouse;
class InputManager;

class Shot : IEntity
{
public:
	Shot(InputManager* p_pxInputManager, Sprite* p_pxSprite, int p_iScreenWidth, int p_iScreenHeight);
	~Shot();
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
	Mouse* m_pxMouse;
	InputManager* m_pxInputManager;
	float m_fSpeed;
	float m_fDirY;
	float m_fX;
	float m_fY;
	int m_iScreenWidth;
	int m_iScreenHeight;
	bool m_bVisible;
	bool m_bActive;
};