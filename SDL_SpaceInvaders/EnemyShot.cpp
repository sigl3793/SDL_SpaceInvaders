#include "stdafx.h"
#include "EnemyShot.h"
#include "Sprite.h"
#include "Collider.h"
#include "Mouse.h"
#include "InputManager.h"

EnemyShot::EnemyShot(InputManager* p_pxInputManager,Sprite* p_pxSprite, int p_iScreenWidth, int p_iScreenHeight)
{
	m_pxInputManager = p_pxInputManager;
	m_pxSprite = p_pxSprite;
	m_iScreenWidth = p_iScreenWidth;
	m_iScreenHeight = p_iScreenHeight;
	m_fSpeed = 0.0f;
	m_fDirY = 0.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_bVisible = false;
	m_bActive = false;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	srand(time(0));
}

EnemyShot::~EnemyShot()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void EnemyShot::Update(float p_fDeltaTime)
{
	int shoot = 1 + (rand() % 5000);
	if (m_bActive)
	{
		m_fY += m_fDirY * m_fSpeed * p_fDeltaTime;
		if (m_fY < 0)
		{
			m_fY = 0;
			Deactivate();
		}
		m_pxCollider->Refresh();
	}
	if (shoot == 1)
	{
		Activate();
	}
}

Sprite* EnemyShot::GetSprite()
{
	return m_pxSprite;
}

Collider* EnemyShot::GetCollider()
{
	return m_pxCollider;
}

float EnemyShot::GetX()
{
	return m_fX;
}

float EnemyShot::GetY()
{
	return m_fY;
}

bool EnemyShot::IsVisible()
{
	return m_bVisible;
}

bool EnemyShot::IsActive()
{
	return m_bActive;
}

EENTITYTYPE EnemyShot::GetType()
{
	return EENTITYTYPE::ENTITY_ENEMYSHOT;
}

void EnemyShot::Activate()
{
	m_bActive = true;
	m_fSpeed = 500.0f;
	m_fDirY = 1.0f;
}

void EnemyShot::Deactivate()
{
	m_bActive = false;
}

void EnemyShot::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider->Refresh();
}