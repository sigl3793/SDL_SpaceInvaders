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
	m_fSpeed = 200.0f;
	m_fDirX = 1.0f;
	m_fDirY = 1.0f;
	m_iScreenHeight = 768;
	m_iScreenWidth = 1024;
	
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
		SDL_Log("Position X:%f Y:%f", m_fX, m_fY);
		m_fX += m_fDirX * m_fSpeed * p_fDeltaTime;

		if (m_fX <= 0)
		{
			m_fX = 0;
			m_fY += 10;
			ReverseDirectionX();
		}
		if (m_fX + m_pxSprite->GetRegion()->w > m_iScreenWidth)
		{
			m_fX = m_iScreenWidth - m_pxSprite->GetRegion()->w;
			m_fY += 10;
			ReverseDirectionX();
			//SDL_Log("Direction Changed");
			//m_fX + m_pxSprite->GetRegion()->w > m_iScreenWidth
			//m_fX >= 1000
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

void Invader::SetDirectionY(float p_fDirY)
{
	m_fDirY = p_fDirY;
}

void Invader::ReverseDirectionX()
{
	m_fDirX *= -1;
	//m_fX += m_fDirX * m_fSpeed;
}

