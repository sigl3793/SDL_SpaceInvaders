#include "stdafx.h"
#include "Invader.h"
#include "Collider.h"
#include "Sprite.h"
#include "Engine.h"
#include <iostream>

//int ammo = 5;

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
	m_fSpeed = 0.0f;
	m_fISpeed = 0.0f;
	m_fDirX = 1.0f;
	m_fDirY = 0.0f;
	m_iScreenHeight = 768;
	m_iScreenWidth = 1024;
	
	m_bIncrease = false;
}

Invader::~Invader()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Invader::Update(float p_fDeltaTime)
{	
	/*int chance = rand() % 100 + 1;
	if (chance > 75)
	{
		ammo -= 1;
	}*/

	if (m_bActive)
	{
		//SDL_Log("Position X:%f Y:%f", m_fX, m_fY);
		m_fX += m_fDirX * (m_fSpeed+m_fISpeed) * p_fDeltaTime;
		m_pxCollider->Refresh();
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
	m_fSpeed = 100.0f;
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

void Invader::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider->Refresh();
}

void Invader::ReverseDirectionX()
{
	m_fY += 10;
	m_fDirX *= -1.0f;
}

bool Invader::IncreaseSpeed()
{
	m_fISpeed = 50.0f;
	return m_bIncrease;
}
