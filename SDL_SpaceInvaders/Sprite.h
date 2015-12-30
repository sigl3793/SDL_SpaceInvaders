#pragma once

class Sprite
{
public:
	Sprite(SDL_Texture* p_pxTexture);
	Sprite(SDL_Texture* p_pxTexture, int p_iX, int p_iY, int p_iW, int p_iH);
	~Sprite();
	SDL_Texture* GetTexture(); // kan vara virtual
	SDL_Rect* GetRegion(); // kan g�ra till virtual
protected:
	SDL_Texture* m_pxTexture; // d� blir detta en on�dig pekare
	SDL_Rect m_xRegion;
	//lista med frame data
};
