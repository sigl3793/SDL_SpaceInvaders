#include "stdafx.h"
#include "DrawManager.h"
#include "Sprite.h"

DrawManager::DrawManager()
{
}

DrawManager::~DrawManager()
{
}

bool DrawManager::Initialize(int p_iWidht, int p_iHeight)
{
	// Creates an SDL_Window with the params (name, position_x, position_y, width, height, flags) parameters.
	m_pxWindow = SDL_CreateWindow("Space Invaders",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		p_iWidht, p_iHeight, SDL_WINDOW_OPENGL);

	// If the returned pointer is a nullptr something has gone wrong and we must quit.
	if (m_pxWindow == nullptr)
	{
		return false;
	}

	// Creates a renderer connected to the window we created earlier.
	m_pxRenderer = SDL_CreateRenderer(m_pxWindow,
		-1, SDL_RENDERER_ACCELERATED);

	// If the returned pointer is a nullptr something has gone wrong and we must quit.
	if (m_pxRenderer == nullptr)
	{
		const char* error = SDL_GetError();
		return false;
	}

	SDL_SetRenderDrawColor(m_pxRenderer,
		0x00, 0x00, 0x00, 0xff);

	return true;

}

void DrawManager::Shutdown()
{
	SDL_DestroyRenderer(m_pxRenderer);

	SDL_DestroyWindow(m_pxWindow);
}

void DrawManager::Clear()
{
	SDL_RenderClear(m_pxRenderer);
}

void DrawManager::Present()
{
	SDL_RenderPresent(m_pxRenderer);
}

void DrawManager::Draw(Sprite* p_pxSprite, int p_iX, int p_iY)
{
	// Creates a destination rect by combining the position parameters with the Sprite region data. This is later used to know where and how big will
	// render thic picture.
	SDL_Rect rect = 
	{
		p_iX, p_iY, p_pxSprite->GetRegion()->w, p_pxSprite->GetRegion()->h 
	};

	// RenderCopy renders a source rectangle from a texture to a target rectangle on a renderer. Then we render the piece the Sprites Region specifies
	// of the Sprites SDL_Texture to the correct destination we created earlier.
	SDL_RenderCopy(m_pxRenderer, p_pxSprite->GetTexture(), p_pxSprite->GetRegion(), &rect);
}

SDL_Renderer* DrawManager::GetRenderer()
{
	return m_pxRenderer;
}
