#ifndef __GUIVIEWPORT_H__
#define __GUIVIEWPORT_H__

#include "Gui.h"

class GuiViewport : public Gui
{
public:
	GuiViewport(SDL_Rect* position_size, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiViewport(SDL_Rect* position_size, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiViewport();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void push_back_item(Gui* newitem);

private:
	void DebugDraw() const;

private:
	SDL_Rect Viewport = { 0,0,0,0 };
	std::list<Gui*> ViewportElements;
};

#endif // __GUIVIEWPORT_H__