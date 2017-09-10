#ifndef __GUISCROLLBAR_H__
#define __GUISCROLLBAR_H__

#include "Gui.h"

class GuiScrollBar : public Gui
{

/*
public:
	GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, bool vertical, bool movable, AddGuiTo addto);
	GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hoverorpressedtexture, bool vertical, bool movable, AddGuiTo addto);
	GuiScrollBar(iPoint position, SDL_Rect* scrollbarbackground, SDL_Rect* scrollbarbar, std::string* bottonstr, ButtonType type, SDL_Rect* idletexture, SDL_Rect* hovertexture, SDL_Rect* pressedtexture, bool vertical, bool movable, AddGuiTo addto);
	~GuiScrollBar();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void EditButtonStr(std::string* newstr);
	float GetPercentualValue() const;

private:
	void DebugDraw() const;
	void CalculateScrollMinMax(SDL_Rect* scrollbarbackground);

private:
	GuiButton* ScrollBarButton = nullptr;
	SDL_Rect scrollbarbackground = { 0,0,0,0 };
	SDL_Rect scrollbarbar = { 0,0,0,0 };
	iPoint ButtonWH = { 0,0 };
	bool has_bar = true;
	bool vertical = true;
	int scroll_max_value = 0;
	int scroll_min_value = 0;
	float percentualvalue = 0.0f;
*/
};

#endif // __GUISCROLLBAR_H__