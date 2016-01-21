#pragma once

class Sprite;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();
	bool Initialize(int p_iWidth, int p_iHeight);
	void Shutdown();
	void Clear();
	void Present();
	void Draw(Sprite* p_pxSprite, float p_fX, float p_fY);
	SDL_Renderer* GetRenderer();

private:
	SDL_Window* m_pxWindow = nullptr;
	SDL_Renderer* m_pxRenderer = nullptr;
};