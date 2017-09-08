#ifndef __GUIWINDOW_H__
#define __GUIWINDOW_H__

#include "Gui.h"

class GuiWindow : public Gui
{
public:
	//elementneme is the name of the element type that you want to use, this name is the one asigned in the Atlas XML file
	GuiWindow(char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiWindow(char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiWindow();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	void push_back_item(Gui* newitem);

	void SetAnimationFrameMiliseconds(int frameMiliseconds);

private:
	void CommonConstructor(iPoint position, std::string* elementname);
	void DebugDraw() const;

private:
	Animation WindowAnimation;
	SDL_Texture* Atlas = nullptr;
	std::list<Gui*> WindowElements;
	iPoint OriginalPosition = { 0,0 };
};

#endif // __GUIWINDOW_H__