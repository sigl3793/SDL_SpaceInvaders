#include "stdafx.h"
#include "Player.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"
#include "InputManager.h"

Player::Player(InputManager* p_pxInputManager, Sprite* p_pxSprite, float p_fX, float p_fY, int p_iScreenWidth)
{
	m_pxInputManager = p_pxInputManager;
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_iScreenWidth = p_iScreenWidth;
	m_bVisible = true;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
}

Player::~Player()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Player::Update(float p_fDeltaTime)
{
	//m_fX = m_pxInputManager->GetMouse()->GetX() - m_pxSprite->GetRegion()->w / 2;
	//m_fX = m_iScreenWidth / 2;
	if (m_fX < 0)
	{
		m_fX = 0;
	}
	if ((m_fX + m_pxSprite->GetRegion()->w) > m_iScreenWidth)
	{
		//m_fX = m_iScreenWidth - m_pxSprite->GetRegion()->w;
		m_fX = 966;
	}

	if (m_pxInputManager->GetKeyboard()->IsKeyDown(4))
	{
		m_fX -= 3;
	}
	if (m_pxInputManager->GetKeyboard()->IsKeyDown(7))
	{
		m_fX += 3;
	}
	m_pxCollider->Refresh();
}

Sprite* Player::GetSprite() 
{ 
	return m_pxSprite; 
}

Collider* Player::GetCollider()
{
	return m_pxCollider;
}

float Player::GetX() 
{ 
	return m_fX; 
}

float Player::GetY()
{ 
	return m_fY;
}

bool Player::IsVisible() 
{ 
	return m_bVisible;
}

EENTITYTYPE Player::GetType() 
{ 
	return EENTITYTYPE::ENTITY_PLAYER; 
}