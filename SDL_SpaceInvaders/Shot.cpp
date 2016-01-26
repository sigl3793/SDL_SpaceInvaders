#include "stdafx.h"
#include "Shot.h"
#include "Sprite.h"
#include "Collider.h"
#include "Mouse.h"
#include "InputManager.h"

Shot::Shot(InputManager* p_pxInputManager, Sprite* p_pxSprite, int p_iScreenWidth, int p_iScreenHeight)
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

}

Shot::~Shot()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Shot::Update(float p_fDeltaTime)
{
	if (m_bActive)
	{
		m_fX += m_fSpeed*(cos(bullet_direction))*p_fDeltaTime;
		m_fY += m_fSpeed*(sin(bullet_direction))*p_fDeltaTime;
		m_pxCollider->Refresh();

		if (m_fY < 0)
		{
			m_fY = 0;
			Deactivate();
		}
		m_pxCollider->Refresh();
		if (m_fX > 1024 || m_fX < 0)
		{
			Deactivate();
		}
	}

	if (m_pxInputManager->GetMouse()->IsButtonDown(1) && m_bActive != true)
	{
		Activate();
		m_pxInputManager->GetMouse()->SetButton(1, false);
	}
}

Sprite* Shot::GetSprite()
{
	return m_pxSprite;
}

Collider* Shot::GetCollider()
{
	return m_pxCollider;
}

float Shot::GetX()
{
	return m_fX;
}

float Shot::GetY()
{
	return m_fY;
}

bool Shot::IsVisible()
{
	return m_bVisible;
}

bool Shot::IsActive()
{
	return m_bActive;
}

EENTITYTYPE Shot::GetType()
{
	return EENTITYTYPE::ENTITY_SHOT;
}

void Shot::Activate()
{
	MouseY = m_pxInputManager->GetMouse()->GetY();
	MouseX = m_pxInputManager->GetMouse()->GetX();
	bullet_direction = atan2(MouseY - m_fY, MouseX - m_fX);
	m_fSpeed = 1000.0f;
	m_bActive = true;
}

void Shot::Deactivate()
{
	m_bActive = false;
}

void Shot::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider->Refresh();
}