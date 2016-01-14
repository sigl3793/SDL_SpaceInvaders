#include "stdafx.h"
#include "Defence.h"
#include "Collider.h"
#include "Sprite.h"

Defence::Defence(Sprite* p_pxSprite, float p_fX, float p_fY)
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
}

Defence::~Defence()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Defence::Update(float p_fDeltaTime)
{
	m_pxCollider->Refresh();
}

Sprite* Defence::GetSprite()
{
	return m_pxSprite;
}

Collider* Defence::GetCollider()
{
	return m_pxCollider;
}

float Defence::GetX()
{
	return m_fX;
}

float Defence::GetY()
{
	return m_fY;
}

bool Defence::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Defence::GetType()
{
	return EENTITYTYPE::ENTITY_DEFENCE;
}

void Defence::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider->Refresh();
}

void Defence::SetVisible(bool p_bValue)
{
	m_bVisible = p_bValue;
}