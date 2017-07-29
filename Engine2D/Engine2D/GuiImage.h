#ifndef __GUIIMAGE_H__
#define __GUIIMAGE_H__

#include "Gui.h"

class GuiImage : public Gui
{
public:
	//elementneme is the name of the element type that you want to use, this name is the one asigned in the Atlas XML file
	GuiImage(char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiImage(char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiImage();

	void Draw();

	void SetAnimationFrameMiliseconds(int frameMiliseconds);

private:
	void CommonConstructor(iPoint position, std::string* elementname);
	void DebugDraw() const;

private:
	Animation ImageAnimation;
	SDL_Texture* Atlas;
};

#endif // __GUIIMAGE_H__