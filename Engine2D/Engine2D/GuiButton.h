#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "Gui.h"

class GuiLabel;

enum GuiButtonState
{
	GuiButtonState_idle,
	GuiButtonState_hover,
	GuiButtonState_pressed
};

class GuiButton : public Gui
{
public:
	//elementneme is the name of the element type that you want to use, this name is the one asigned in the Atlas XML file
	GuiButton(char* str, ButtonType type, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiButton(char* str, ButtonType type, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiButton();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();

	void SetAnimationFrameMiliseconds(GuiButtonState statetochange, int frameMiliseconds);

private:
	void CommonConstructor(ButtonType type, iPoint position, std::string* elementname);
	void DebugDraw() const;

private:
	ButtonType Type = ButtonType::null_ButtonType;
	Animation ButtonAnimationIdle;
	Animation ButtonAnimationHover;
	Animation ButtonAnimationPressed;
	SDL_Texture* Atlas = nullptr;
	GuiLabel* ButtonString = nullptr;
	Animation* ActualButtonAnimation = nullptr;
};

#endif // __GUIBUTTON_H__