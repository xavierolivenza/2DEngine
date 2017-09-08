#include "GuiButton.h"
#include "GuiLabel.h"
#include "j1Gui.h"

GuiButton::GuiButton(char* str, ButtonType type, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_button, movable, can_focus, move_with_camera, module_listener, addto)
{
	ButtonString = App->gui->CreateLabel(str, "", position, module_listener, false, false, move_with_camera, AddGuiTo::null_AddGuiTo);
	CommonConstructor(type, position, &std::string(elementname));
}

GuiButton::GuiButton(char* str, ButtonType type, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_button, movable, can_focus, move_with_camera, scene_listener, addto)
{
	ButtonString = App->gui->CreateLabel(str, "", position, scene_listener, false, false, move_with_camera, AddGuiTo::null_AddGuiTo);
	CommonConstructor(type, position, &std::string(elementname));
}

void GuiButton::CommonConstructor(ButtonType type, iPoint position, std::string* elementname)
{
	atlas_button* ButtonType = (atlas_button*)App->gui->GetAtlasPrefab(atlas_element_type::enum_atlas_button, elementname);
	//if this works, i will clean this code to have 0 duplicated structures
	if (ButtonType != nullptr)
	{
		ButtonAnimationIdle.loop = ButtonType->state_idle->animation_loop;
		ButtonAnimationIdle.frameMiliseconds = ButtonType->state_idle->frameMiliseconds;
		ButtonAnimationIdle.frames = ButtonType->state_idle->atlas_element_state_frames;
		switch (type)
		{
		case ButtonType::idle_only:
			//Idle already saved
			break;
		case ButtonType::idle_hover:
			//Idle already saved
			ButtonAnimationHover.loop = ButtonType->state_hover->animation_loop;
			ButtonAnimationHover.frameMiliseconds = ButtonType->state_hover->frameMiliseconds;
			ButtonAnimationHover.frames = ButtonType->state_hover->atlas_element_state_frames;
			break;
		case ButtonType::idle_pressed:
			//Idle already saved
			ButtonAnimationPressed.loop = ButtonType->state_pressed->animation_loop;
			ButtonAnimationPressed.frameMiliseconds = ButtonType->state_pressed->frameMiliseconds;
			ButtonAnimationPressed.frames = ButtonType->state_pressed->atlas_element_state_frames;
			break;
		case ButtonType::idle_hover_pressed:
			//Idle already saved
			ButtonAnimationHover.loop = ButtonType->state_hover->animation_loop;
			ButtonAnimationHover.frameMiliseconds = ButtonType->state_hover->frameMiliseconds;
			ButtonAnimationHover.frames = ButtonType->state_hover->atlas_element_state_frames;

			ButtonAnimationPressed.loop = ButtonType->state_pressed->animation_loop;
			ButtonAnimationPressed.frameMiliseconds = ButtonType->state_pressed->frameMiliseconds;
			ButtonAnimationPressed.frames = ButtonType->state_pressed->atlas_element_state_frames;
			break;
		default:
			LOG("Invalid ButtonType in CommonConstructor of GuiButton");
		}
		Type = type;
		Atlas = ButtonType->Atlas_texture;
		ActualButtonAnimation = &ButtonAnimationIdle;
		Gui_Collider = { position.x,position.y,ButtonType->Collider.w,ButtonType->Collider.h };
		CenterStrWithBackground();
		PrevPos = NewPos = position;
	}
	else
		LOG("Error Loading Image %s", elementname->c_str());
}

GuiButton::~GuiButton()
{
	
}

void GuiButton::Update(const Gui* mouse_hover, const Gui* focus)
{
	if ((mouse_hover == (Gui*)this) || (focus == this))
	{
		switch (Type)
		{
		case ButtonType::idle_hover:
			ActualButtonAnimation = &ButtonAnimationHover;
			break;
		case ButtonType::idle_pressed:
			ActualButtonAnimation = &ButtonAnimationIdle;
			if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN) || (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT))
				ActualButtonAnimation = &ButtonAnimationPressed;
			break;
		case ButtonType::idle_hover_pressed:
			ActualButtonAnimation = &ButtonAnimationHover;
			if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN) || (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT))
				ActualButtonAnimation = &ButtonAnimationPressed;
			break;
		}
	}
	else
		ActualButtonAnimation = &ButtonAnimationIdle;

	NewPos = this->GetLocalPos();
	if (NewPos != PrevPos)
	{
		iPoint ButtonNewPos = ButtonString->GetLocalPos();
		int x = 0;
		int y = 0;
		App->input->GetMouseMotion(x, y);
		ButtonNewPos.x += x;
		ButtonNewPos.y += y;
		ButtonString->SetLocalPos(ButtonNewPos.x, ButtonNewPos.y);
		CenterStrWithBackground();
		PrevPos = NewPos;
	}
}

void GuiButton::Draw()
{
	if (this->visible)
	{
		Frame actualFrame = ActualButtonAnimation->GetCurrentFrame();

		if (this->move_with_camera)
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		else
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		ButtonString->Draw();
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiButton::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, GuiButtonDebugColor(0), GuiButtonDebugColor(1), GuiButtonDebugColor(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiButton::SetAnimationFrameMiliseconds(GuiButtonState statetochange, int frameMiliseconds)
{
	switch (statetochange)
	{
	case GuiButtonState::GuiButtonState_idle:
		ButtonAnimationIdle.frameMiliseconds = frameMiliseconds;
		break;
	case GuiButtonState::GuiButtonState_hover:
		ButtonAnimationHover.frameMiliseconds = frameMiliseconds;
		break;
	case GuiButtonState::GuiButtonState_pressed:
		ButtonAnimationPressed.frameMiliseconds = frameMiliseconds;
		break;
	default:
		LOG("Invalid GuiButtonState in SetAnimationFrameMiliseconds of GuiButton");
	}
}

void GuiButton::ChangeStr(std::string* newstr)
{
	ButtonString->ChangeStr(newstr);
}

void GuiButton::SetStrOffset(iPoint newoffset)
{
	ButtonString->SetStrOffset(newoffset);
}

void GuiButton::SetStrOffset(int newoffsetx, int newoffsety)
{
	ButtonString->SetStrOffset(newoffsetx, newoffsety);
}

void GuiButton::CenterStrWithBackground()
{
	int w = 0;
	int h = 0;
	ButtonString->GetLabelWH(w, h);
	SetStrOffset((Gui_Collider.w - w) * 0.5f, (Gui_Collider.h - h) * 0.5f);
}

void GuiButton::SetStrColor(Color* newcolor)
{
	ButtonString->SetStrColor(newcolor);
}

void GuiButton::SetStrColor(uint r, uint g, uint b)
{
	ButtonString->SetStrColor(r, g, b);
}