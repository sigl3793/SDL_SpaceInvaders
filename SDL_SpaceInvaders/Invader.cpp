#include "stdafx.h"
#include "Invader.h"
#include "Collider.h"
#include "Sprite.h"
#include <iostream>

Invader::Invader(Sprite* p_pxSprite,
	float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_bVisible = true;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	m_pxCollider->Refresh();

	m_bActive = true;
	m_fSpeed = 100.0f;
	m_fDirX = 1.0f;
}

Invader::~Invader()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Invader::Update(float p_fDeltaTime)
{	
	if (m_bActive)
	{
		m_fX += m_fDirX * m_fSpeed * p_fDeltaTime;

		if (m_fX + m_pxSprite->GetRegion()->w > m_iScreenWidth)
		{
			m_fX = m_iScreenWidth - m_pxSprite->GetRegion()->w; // denna g�r s� att mina invaders inte syns
			ReverseDirectionX();
		}

	}
}

Sprite* Invader::GetSprite()
{
	return m_pxSprite;
}

Collider* Invader::GetCollider()
{
	return m_pxCollider;
}

float Invader::GetX()
{
	return m_fX;
}

float Invader::GetY()
{
	return m_fY;
}

bool Invader::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Invader::GetType()
{
	return EENTITYTYPE::ENTITY_INVADER;
}

void Invader::SetVisible(bool p_bValue)
{
	m_bVisible = p_bValue;
}

bool Invader::IsActive()
{
	return m_bActive;
}

void Invader::Deactivate()
{
	m_bActive = false;
}

void Invader::SetDirectionX(float p_fDirX)
{
	m_fDirX = p_fDirX;
}

void Invader::ReverseDirectionX()
{
	m_fDirX *= -1;
}
