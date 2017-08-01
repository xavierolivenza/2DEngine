#ifndef __GUIINPUTTEXT_H__
#define __GUIINPUTTEXT_H__

#include "Gui.h"
#include "GuiLabel.h"

class GuiInputText : public Gui
{
public:
	//elementneme is the name of the element type that you want to use, this name is the one asigned in the Atlas XML file
	//elementneme is the same as label types
	GuiInputText(char* str, char* elementname, iPoint position, bool isPassword, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiInputText(char* str, char* elementname, iPoint position, bool isPassword, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiInputText();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw();

	void FocusGained();
	void FocusLost();

	void SetAnimationFrameMiliseconds(int frameMiliseconds);

	void ChangeStr(std::string* newstr);

	void SetStrOffset(iPoint newoffset);
	void SetStrOffset(int newoffsetx, int newoffsety);
	void CenterStrWithBackground();

	void SetStrColor(Color* newcolor);
	void SetStrColor(uint r, uint g, uint b);

private:
	void CommonConstructor();
	void DebugDraw() const;

private:
	GuiLabel* Label = nullptr;
	std::string OriginalStr;
	std::string CurrentStr;
	bool isPassword = false;
	j1Timer edit_timer;

};

#endif // __GUIINPUTTEXT_H__