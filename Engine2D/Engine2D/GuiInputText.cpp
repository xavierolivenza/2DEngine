#include "j1Gui.h"
#include "GuiInputText.h"

GuiInputText::GuiInputText(char* str, char* elementname, iPoint position, bool isPassword, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_inputtext, movable, can_focus, move_with_camera, module_listener, addto)
{
	Label = App->gui->CreateLabel(str, elementname, position, module_listener, movable, can_focus, move_with_camera, AddGuiTo::null_AddGuiTo);
	Gui_Collider = Label->Gui_Collider;
	Label->itsInputText(true);
}

GuiInputText::GuiInputText(char* str, char* elementname, iPoint position, bool isPassword, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_inputtext, movable, can_focus, move_with_camera, scene_listener, addto)
{
	Label = App->gui->CreateLabel(str, elementname, position, scene_listener, movable, can_focus, move_with_camera, AddGuiTo::null_AddGuiTo);
	Gui_Collider = Label->Gui_Collider;
	Label->itsInputText(true);
}

GuiInputText::~GuiInputText()
{

}

void GuiInputText::Update(const Gui* mouse_hover, const Gui* focus)
{
	Label->position.x = position.x;
	Label->position.y = position.y;
}

void GuiInputText::Draw()
{
	Label->Draw();

	if (App->gui->isDebugDrawActive())
		DebugDraw();
}

void GuiInputText::FocusGained()
{
	SDL_StartTextInput();
}

void GuiInputText::FocusLost()
{
	SDL_StopTextInput();
}

void GuiInputText::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, GuiInputTextDebugColor(0), GuiInputTextDebugColor(1), GuiInputTextDebugColor(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiInputText::SetAnimationFrameMiliseconds(int frameMiliseconds)
{
	Label->SetAnimationFrameMiliseconds(frameMiliseconds);
}

void GuiInputText::ChangeStr(std::string* newstr)
{
	Label->ChangeStr(newstr);
}

void GuiInputText::SetStrOffset(iPoint newoffset)
{
	Label->SetStrOffset(newoffset);
}

void GuiInputText::SetStrOffset(int newoffsetx, int newoffsety)
{
	Label->SetStrOffset(newoffsetx, newoffsety);
}

void GuiInputText::CenterStrWithBackground()
{
	Label->CenterStrWithBackground();
}

void GuiInputText::SetStrColor(Color* newcolor)
{
	Label->SetStrColor(newcolor);
}

void GuiInputText::SetStrColor(uint r, uint g, uint b)
{
	Label->SetStrColor(r, g, b);
}