#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "j1Module.h"

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;
	iPoint WorldToScreen(int x, int y) const;

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX, bool use_scale = true, uint opacity = 255, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true, bool use_scale = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true, bool use_scale = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true, bool use_scale = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer = nullptr;
	SDL_Rect		camera = { 0,0,0,0 };
	SDL_Rect		viewport = { 0,0,0,0 };
	SDL_Color		background;
};

#endif // __j1RENDER_H__