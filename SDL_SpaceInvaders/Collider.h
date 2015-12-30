#pragma once

class IEntity;

class Collider
{
public:
	Collider(int p_iWidth, int p_iHeight);
	void SetPosition(int p_iX, int p_iY);
	void SetSize(int p_iWidth, int p_iHeight);
	int GetX();
	int GetY();
	int GetW();
	int GetH();
	void SetParent(IEntity* p_pxParent); // Sets the parent Entity
	void Refresh(); // If the collider has a parent entity it will set its position to the parents position
private:
	Collider() {};
	IEntity* m_pxParent;
	SDL_Rect m_xRegion;
};