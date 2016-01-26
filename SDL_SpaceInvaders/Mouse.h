#pragma once
#include "stdafx.h"
class Mouse
{
public:
	Mouse();
	~Mouse();
	int GetX();
	int GetY();
	void SetPosition(int p_iX, int p_iY);
	bool IsButtonDown(int p_iIndex);
	void SetButton(int p_iIndex, bool p_bValue);

	glm::vec2 getMouseCoords() const { return _mouseCoords; }

private:
	bool m_abButtons[3];
	int m_iX;
	int m_iY;
	glm::vec2 _mouseCoords;

};