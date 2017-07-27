#ifndef __GUIXMLSTORAGE_H__
#define __GUIXMLSTORAGE_H__

#include <vector>
#include "Animation.h"

enum atlas_element_type
{
	enum_atlas_image,
	enum_atlas_label,
	enum_atlas_window,
	enum_atlas_button,
	enum_atlas_scrollbar_vertical,
	enum_atlas_scrollbar_horitzontal,
	enum_atlas_check,
	null_atlas_element_type
};

struct atlas_element
{
	atlas_element(char* name, atlas_element_type type, SDL_Rect* Collider, SDL_Texture* Atlas_texture) : name(name), type(type), Collider(*Collider), Atlas_texture(Atlas_texture)
	{

	}

	std::string name;
	atlas_element_type type = atlas_element_type::null_atlas_element_type;
	SDL_Rect Collider = { 0,0,0,0 };
	SDL_Texture* Atlas_texture = nullptr;
};

struct atlas_image_label_window : public atlas_element
{
	atlas_image_label_window(char* name, atlas_element_type type, bool animation_loop, float animation_speed, std::vector<Frame>* atlas_element_state_frames,
		SDL_Rect* Collider, SDL_Texture* Atlas_texture) :
		animation_loop(animation_loop), animation_speed(animation_speed), atlas_element_state_frames(*atlas_element_state_frames),
		atlas_element(name, type, Collider, Atlas_texture)
	{

	}

	bool animation_loop = false;
	float animation_speed = 0.0f;
	std::vector<Frame> atlas_element_state_frames;
};

struct atlas_button : public atlas_element
{
	atlas_button(char* name, atlas_element_type type, atlas_image_label_window* state_idle, atlas_image_label_window* state_hover,
		atlas_image_label_window* state_pressed, SDL_Rect* Collider, SDL_Texture* Atlas_texture):
		state_idle(state_idle), state_hover(state_hover), state_pressed(state_pressed),
		atlas_element(name, type, Collider, Atlas_texture)
	{

	}

	atlas_image_label_window* state_idle = nullptr;
	atlas_image_label_window* state_hover = nullptr;
	atlas_image_label_window* state_pressed = nullptr;
};

struct atlas_scrollbar : public atlas_element
{
	atlas_scrollbar(char* name, atlas_element_type type, atlas_image_label_window* scrollbar_background, atlas_image_label_window* scrollbar_line,
		atlas_button* scrollbar_button, SDL_Rect* Collider, SDL_Texture* Atlas_texture) :
		scrollbar_background(scrollbar_background), scrollbar_line(scrollbar_line), scrollbar_button(scrollbar_button),
		atlas_element(name, type, Collider, Atlas_texture)
	{

	}

	atlas_image_label_window* scrollbar_background = nullptr;
	atlas_image_label_window* scrollbar_line = nullptr;
	atlas_button* scrollbar_button = nullptr;
};

struct atlas_check : public atlas_element
{
	atlas_check(char* name, atlas_element_type type, atlas_image_label_window* check_unchecked_background, atlas_image_label_window* check_checked_background,
		atlas_image_label_window* check_check, atlas_image_label_window* check_checked_backed_check, SDL_Rect* Collider, SDL_Texture* Atlas_texture) :
		check_unchecked_background(check_unchecked_background), check_checked_background(check_checked_background), check_check(check_check),
		check_checked_backed_check(check_checked_backed_check),
		atlas_element(name, type, Collider, Atlas_texture)
	{

	}

	atlas_image_label_window* check_unchecked_background = nullptr;
	atlas_image_label_window* check_checked_background = nullptr;
	atlas_image_label_window* check_check = nullptr;
	atlas_image_label_window* check_checked_backed_check = nullptr;
};

#endif // __GUIXMLSTORAGE_H__