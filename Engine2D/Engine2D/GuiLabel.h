#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "Gui.h"

class GuiLabel : public Gui
{
public:
	//elementneme is the name of the element type that you want to use, this name is the one asigned in the Atlas XML file
	GuiLabel(char* str, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiLabel(char* str, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiLabel();

	void Draw();

	void SetAnimationFrameMiliseconds(int frameMiliseconds);

private:
	void CommonConstructor(iPoint position, std::string* str, std::string* elementname);
	void DebugDraw() const;

private:
	bool hasBackground = false;
	Animation LabelBackgroundAnimation;
	SDL_Texture* Atlas;
	std::string str;
};

#endif // __GUILABEL_H__