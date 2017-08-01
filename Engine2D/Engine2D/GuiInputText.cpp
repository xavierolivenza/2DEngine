#include <cctype>

#include "j1Gui.h"
#include "GuiInputText.h"
#include "j1Input.h"

GuiInputText::GuiInputText(char* str, char* elementname, iPoint position, bool isPassword, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_inputtext, movable, can_focus, move_with_camera, module_listener, addto)
{
	Label = App->gui->CreateLabel(str, elementname, position, module_listener, movable, can_focus, move_with_camera, AddGuiTo::null_AddGuiTo);
	CommonConstructor();
}

GuiInputText::GuiInputText(char* str, char* elementname, iPoint position, bool isPassword, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_inputtext, movable, can_focus, move_with_camera, scene_listener, addto)
{
	Label = App->gui->CreateLabel(str, elementname, position, scene_listener, movable, can_focus, move_with_camera, AddGuiTo::null_AddGuiTo);
	CommonConstructor();
}

void GuiInputText::CommonConstructor()
{
	Gui_Collider = Label->Gui_Collider;
	Label->itsInputText(true);
	OriginalStr = CurrentStr = Label->str;
	writingPos = CurrentStr.size();
	edit_timer.Start();
}

GuiInputText::~GuiInputText()
{

}

void GuiInputText::Update(const Gui* mouse_hover, const Gui* focus)
{
	Label->position.x = position.x;
	Label->position.y = position.y;

	if (focus == this)
	{
		std::string* newstrtoadd = App->input->GetInputText();
		if (newstrtoadd != nullptr)
			if (std::isalnum((*newstrtoadd)[0]))
			{
				CurrentStr.insert(writingPos, *newstrtoadd);
				writingPos++;
				Label->ChangeStr(&CurrentStr);
			}
		if (CurrentStr.size() > 0)
		{
			if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == j1KeyState::KEY_REPEAT)
			{
				if (edit_timer.ReadSec() >= 0.05f)
				{
					CurrentStr.erase(writingPos, 1);
					Label->ChangeStr(&CurrentStr);
					writingPos--;
					edit_timer.Start();
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == j1KeyState::KEY_UP)
				writingPos++;
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == j1KeyState::KEY_REPEAT)
			{
				if (edit_timer.ReadSec() >= 0.1f)
					if (writingPos > 0)
					{
						writingPos--;
						edit_timer.Start();
					}
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == j1KeyState::KEY_REPEAT)
			{
				if (edit_timer.ReadSec() >= 0.1f)
				{
					if (writingPos < CurrentStr.size())
					{
						writingPos++;
						edit_timer.Start();
					}
				}
			}
		}
	}
	
	
}

void GuiInputText::Draw()
{
	Label->Draw();

	//Draw input bar to know where of the label are you editing

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