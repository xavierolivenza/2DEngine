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
	}
	else
		LOG("Error Loading Image %s", elementname->c_str());
}

GuiButton::~GuiButton()
{
	
}

void GuiButton::Update(const Gui* mouse_hover, const Gui* focus)
{
	/*
	bool inside = (mouse_hover == (Gui*)this);

	if ((inside == true) || (focus == this))
	{
		switch (button_type)
		{
		case ButtonType::idle_hover:
			curent_state_texture = &hover_texture_rect;
			break;
		case ButtonType::idle_pressed:
			curent_state_texture = &idle_texture_rect;
			if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN) || (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT))
				curent_state_texture = &pressed_texture_rect;
			break;
		case ButtonType::idle_hover_pressed:
			curent_state_texture = &hover_texture_rect;
			if ((App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN) || (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT))
				curent_state_texture = &pressed_texture_rect;
			break;
		}
	}
	else
	{
		curent_state_texture = &idle_texture_rect;
	}
	if (OriginalPosition != position)
	{
		CenterStr();
		ButtonString->SetLocalPos(ButtonStringPos.x, ButtonStringPos.y);
	}
	*/
}

void GuiButton::Draw()
{
	if (this->visible)
	{
		/*
		Frame actualFrame = ImageAnimation.GetCurrentFrame();

		if (this->move_with_camera)
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		else
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		*/
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
	/*
	//Button
	App->render->Blit(atlas, position.x - App->render->camera.x, position.y - App->render->camera.y, curent_state_texture, 1.0f, 0, INT_MAX, INT_MAX, false, opacity);
	//Label
	ButtonString->Draw();
	*/
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