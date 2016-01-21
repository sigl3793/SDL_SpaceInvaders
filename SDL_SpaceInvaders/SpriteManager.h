#pragma once

class Sprite;

class SpriteManager
{
public:
	SpriteManager(SDL_Renderer* p_pxRenderer);
	~SpriteManager();
	Sprite* CreateSprite(const std::string& p_sFilepath, float p_fX, float p_fY, float p_fW, float p_fH);
	void DestroySprite(Sprite* p_xSprite);

private:
	SpriteManager();
	SDL_Renderer* m_pxRenderer;
	std::vector<Sprite*> m_apxSprites;
	std::map<std::string, SDL_Texture*> m_apxTextures;
};
