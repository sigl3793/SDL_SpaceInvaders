#pragma once

class Sprite
{
public:
	Sprite(SDL_Texture* p_pxTexture);
	Sprite(SDL_Texture* p_pxTexture, int p_iX, int p_iY, int p_iW, int p_iH);
	~Sprite();
	SDL_Texture* GetTexture(); // kan vara virtual
	SDL_Rect* GetRegion(); // kan göra till virtual
protected:
	SDL_Texture* m_pxTexture; // då blir detta en onödig pekare
	SDL_Rect m_xRegion;
	//lista med frame data
};
