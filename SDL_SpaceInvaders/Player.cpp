#include "stdafx.h"
#include "Player.h"
#include "Mouse.h"
#include "Sprite.h"
#include "Collider.h"

Player::Player(Mouse* p_pxMouse, Sprite* p_pxSprite,
	float p_fX, float p_fY, int p_iScreenWidth)
{
	m_pxMouse = p_pxMouse;
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_iScreenWidth = p_iScreenWidth;
	m_bVisible = true;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);

	//m_bShoot = p_bShoot;
}

Player::~Player()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}
void Player::Update(float p_fDeltaTime)
{
	m_fX = m_pxMouse->GetX() - m_pxSprite->GetRegion()->w / 2;
	if (m_fX < 0)
	{
		m_fX = 0;
	}
	//   posx + bredd > screenwidth
	//   ________. <- that point
	//
	if ((m_fX + m_pxSprite->GetRegion()->w) > m_iScreenWidth)
	{
		m_fX = m_iScreenWidth - m_pxSprite->GetRegion()->w;
	}
	m_pxCollider->Refresh();
}

Sprite* Player::GetSprite() { return m_pxSprite; }

Collider* Player::GetCollider()
{
	return m_pxCollider;
}

float Player::GetX() { return m_fX; }

float Player::GetY() { return m_fY; }

bool Player::IsVisible() { return m_bVisible; }

EENTITYTYPE Player::GetType() { return EENTITYTYPE::ENTITY_PLAYER; }


/*void Player::Shoot(p_bShoot)
{
	if (m_bActive == false)
	{
		m_bActive = true;
		m_fSpeed = 200;
		// Use our Utility class RandomFloat to get a random value between -2 and 2, this will make
		// the ball fly in an initially random direction
		m_fDirX = Utility::RandomFloat(-2.0f, 2.0f);
		m_fDirY = -1.0f;
	}
}*/
