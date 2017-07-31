#ifndef __GUILABEL_H__
#define __GUILABEL_H__

#include "Gui.h"

struct _TTF_Font;

class GuiLabel : public Gui
{
public:
	//elementneme is the name of the element type that you want to use, this name is the one asigned in the Atlas XML file
	GuiLabel(char* str, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto);
	GuiLabel(char* str, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto);
	~GuiLabel();

	void Draw();

	void SetAnimationFrameMiliseconds(int frameMiliseconds);

	void ChangeStr(char* newstr);
	void ChangeStr(std::string* newstr);

	void SetStrOffset(iPoint newoffset);
	void SetStrOffset(int newoffsetx, int newoffsety);
	void CenterStrWithBackground();

	void SetStrColor(Color* newcolor);
	void SetStrColor(uint r, uint g, uint b);

private:
	void CommonConstructor(iPoint position, std::string* str, std::string* elementname);
	void DebugDraw() const;
	void UpdateStr();

private:
	bool hasBackground = false;
	Animation LabelBackgroundAnimation;
	SDL_Texture* Atlas;
	std::string str;
	bool str_modified = false;
	SDL_Texture* StrTexture = nullptr;
	iPoint offset = { 0,0 };
	Color color = White;
	_TTF_Font* font = nullptr;
};

#endif // __GUILABEL_H__