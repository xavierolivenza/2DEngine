#include <ctime>

#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Input.h"

#define VSYNC true

j1Render::j1Render() : j1Module()
{
	name = "renderer";
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
j1Render::~j1Render()
{}

// Called before render is available
bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if (config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = App->win->screen_surface->w;
		camera.h = App->win->screen_surface->h;
		camera.x = App->win->screen_surface->w / 2;
		camera.y = 0;
	}

	return ret;
}

// Called before the first frame
bool j1Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

// Called each loop iteration
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

// Called each loop iteration
bool j1Render::Update(float dt)
{
	return true;
}

// Called after all Updates
bool j1Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
	SDL_RenderPresent(renderer);

	//Code to take some sshoots
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		// current date/time based on current system
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		// print various components of tm structure.
		//LOG("Year %i, Month %i, Day %i, Time %i:%i:%i", 1900 + ltm.tm_year, 1 + ltm.tm_mon, ltm.tm_mday, ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
		int w, h = 0;
		SDL_GetRendererOutputSize(renderer, &w, &h);
		SDL_Surface *sshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		static char tmp_string[4096];
		sprintf_s(tmp_string, 4096, "screenshot_%i%i%i_%i%i%i.bmp", ltm.tm_mday, 1 + ltm.tm_mon, 1900 + ltm.tm_year, ltm.tm_hour, ltm.tm_min, ltm.tm_sec);
		SDL_SaveBMP(sshot, tmp_string);
		SDL_FreeSurface(sshot);
	}

	return true;
}

// Called before quitting
bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

iPoint j1Render::ScreenToWorld(int x, int y) const
{
	iPoint ret(0, 0);
	float scale = App->win->GetScale();

	ret.x = (int)((float)(x - camera.x) / scale);
	ret.y = (int)((float)(y - camera.y) / scale);

	return ret;
}

iPoint j1Render::WorldToScreen(int x, int y) const
{
	iPoint ret(0, 0);
	float scale = App->win->GetScale();

	ret.x = (int)((float)(x)+camera.x);
	ret.y = (int)((float)(y)+camera.y);

	return ret;
}

// Blit to screen
bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivot_x, int pivot_y, bool use_scale, uint opacity, SDL_RendererFlip flip) const
{
	bool ret = true;
	float scale = 1.0f;
	if (use_scale)
		scale = App->win->GetScale();

	fPoint  f_rect = { 0.0f,0.0f };

	SDL_Rect rect = { 0,0,0,0 };

	rect.x = (int)(camera.x * speed) + (int)(x * scale);
	rect.y = (int)(camera.y * speed) + (int)(y * scale);
	if (section != NULL)
	{
		rect.w = section->w;
		f_rect.x = (float)section->w;
		rect.w = section->h;
		f_rect.y = (float)section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		f_rect.x = (float)rect.w;
		f_rect.y = (float)rect.h;
	}

	f_rect.x *= scale;
	f_rect.y *= scale;
	rect.w = (int)(ceil(f_rect.x));
	rect.h = (int)(ceil(f_rect.y));

	SDL_Point* p = NULL;
	SDL_Point pivot = { 0,0 };

	if (pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}
	if (SDL_SetTextureAlphaMod(texture, opacity) < 0)
	{
		//LOG("Cannot set texture opacity. SDL_SetTextureAlphaMod error: %s", SDL_GetError());
		ret = false;
	}
	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, flip) != 0)
	{
		//LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera, bool use_scale) const
{
	bool ret = true;
	float scale = 1.0f;
	if (use_scale)
		scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w = (int)(rec.w * scale);
		rec.h = (int)(rec.h * scale);
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera, bool use_scale) const
{
	bool ret = true;
	float scale = 1.0f;
	if (use_scale)
		scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if (use_camera)
		result = SDL_RenderDrawLine(renderer, (int)(camera.x + x1 * scale), (int)(camera.y + y1 * scale), (int)(camera.x + x2 * scale), (int)(camera.y + y2 * scale));
	else
		result = SDL_RenderDrawLine(renderer, (int)(x1 * scale), (int)(y1 * scale), (int)(x2 * scale), (int)(y2 * scale));

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera, bool use_scale) const
{
	bool ret = true;
	float scale = 1.0f;
	if (use_scale)
		scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for (uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}