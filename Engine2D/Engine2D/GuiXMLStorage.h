#ifndef __GUIXMLSTORAGE_H__
#define __GUIXMLSTORAGE_H__

#include <list>

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
	atlas_element(char* name, atlas_element_type type) : name(name), type(type)
	{

	}

	std::string name;
	atlas_element_type type = atlas_element_type::null_atlas_element_type;
};

struct atlas_image_label_window : public atlas_element
{
	atlas_image_label_window(char* name, atlas_element_type type, bool animation_loop, float animation_speed, std::list<SDL_Rect>* atlas_element_state_rects) :
		animation_loop(animation_loop), animation_speed(animation_speed), atlas_element_state_rects(*atlas_element_state_rects),
		atlas_element(name, type)
	{

	}

	bool animation_loop = false;
	float animation_speed = 0.0f;
	std::list<SDL_Rect> atlas_element_state_rects;
};

struct atlas_button : public atlas_element
{
	atlas_image_label_window* state_idle = nullptr;
	atlas_image_label_window* state_hover = nullptr;
	atlas_image_label_window* state_pressed = nullptr;
};

struct atlas_scrollbar_vertical : public atlas_element
{
	atlas_image_label_window* scrollbar_vertical_background = nullptr;
	atlas_image_label_window* scrollbar_vertical_line = nullptr;
	atlas_button* scrollbar_vertical_button = nullptr;
};

struct atlas_scrollbar_horitzontal : public atlas_element
{
	atlas_image_label_window* scrollbar_horitzontal_background = nullptr;
	atlas_image_label_window* scrollbar_horitzontal_line = nullptr;
	atlas_button* scrollbar_horitzontal_button = nullptr;
};

struct atlas_check : public atlas_element
{
	atlas_image_label_window* check_unchecked_background = nullptr;
	atlas_image_label_window* check_checked_background = nullptr;
	atlas_image_label_window* check_check = nullptr;
	atlas_image_label_window* check_checked_backed_check = nullptr;
};

#endif // __GUIXMLSTORAGE_H__