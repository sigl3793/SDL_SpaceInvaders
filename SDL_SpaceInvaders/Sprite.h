#pragma once

class Sprite
{
public:
	Sprite(SDL_Texture* p_pxTexture);
	Sprite(SDL_Texture* p_pxTexture, float p_fX, float p_fY, float p_fW, float p_fH);
	~Sprite();
	SDL_Texture* GetTexture();
	SDL_Rect* GetRegion();

protected:
	SDL_Texture* m_pxTexture;
	SDL_Rect m_xRegion;
};
