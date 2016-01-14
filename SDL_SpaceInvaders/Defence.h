#pragma once

#include "IEntity.h"

class Defence : public IEntity
{
public:
	Defence(Sprite* p_pxSprite, float p_fX, float p_fY);
	~Defence();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EENTITYTYPE GetType();
	void SetPosition(float p_fX, float p_fY);
	void SetVisible(bool p_bValue);

private:
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	float m_fX;
	float m_fY;
	bool m_bVisible;
};