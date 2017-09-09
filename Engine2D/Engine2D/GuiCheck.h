#ifndef __GUICHECK_H__
#define __GUICHECK_H__

#include "Gui.h"

class GuiCheck : public Gui
{
public:
	GuiCheck(char* elementname, bool stat, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiCheck(char* elementname, bool stat, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiCheck();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();
	bool Stat() const;

private:
	void CommonConstructor(iPoint position, std::string* elementname);
	void DebugDraw() const;

private:
	Animation check_unchecked_background_Animation;
	Animation check_checked_background_Animation;
	Animation check_check_Animation;
	Animation check_checked_backed_check_Animation;
	SDL_Texture* Atlas = nullptr;
	bool stat = false;
	Animation* ActualCheckAnimation = nullptr;
	bool threeTex = false;
};

#endif // __GUICHECK_H__