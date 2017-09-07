#include "Gui.h"

#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Render.h"
#include "MainScene.h"

Gui::Gui(iPoint position, GuiType type, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo purpose) :
	position(position), movable(movable), type(type), can_focus(can_focus), move_with_camera(move_with_camera), module_listener(module_listener), purpose(purpose)
{
	if (movable)
		SetDragVelocity(1.0f, 1.0f);
}

Gui::Gui(iPoint position, GuiType type, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo purpose) :
	position(position), movable(movable), type(type), can_focus(can_focus), move_with_camera(move_with_camera), scene_listener(scene_listener), purpose(purpose)
{
	if (movable)
		SetDragVelocity(1.0f, 1.0f);
}

void Gui::SetLocalPos(int x, int y)
{
	position.x = Gui_Collider.x = x;
	position.y = Gui_Collider.y = y;

	if (movable && !move_with_camera)
	{
		iPoint Gui_ColliderXY = App->render->WorldToScreen(x, y);
		Gui_Collider.x = Gui_ColliderXY.x;
		Gui_Collider.y = Gui_ColliderXY.y;
	}
	/*
	position.x = x;
	position.y = y;
	iPoint Gui_ColliderXY = App->render->WorldToScreen(x, y);
	Gui_Collider.x = Gui_ColliderXY.x;
	Gui_Collider.y = Gui_ColliderXY.y;
	*/
}

iPoint Gui::GetLocalPos() const
{
	return position;
}

void Gui::GetLocalPos(int& x, int& y) const
{
	x = position.x;
	y = position.y;
}

void Gui::Move(int x, int y)
{
	//Here may have an isue with camera movement like it happened in SetLocalPos
	position.x += x;
	Gui_Collider.x = position.x;
	position.y += y;
	Gui_Collider.y = position.y;
}

void Gui::SetDragVelocity(float x, float y)
{
	drag_vel.x = x;
	drag_vel.y = y;
}

fPoint Gui::GetDragVelocity() const
{
	return drag_vel;
}

void Gui::GetDragVelocity(float& x, float& y) const
{
	x = drag_vel.x;
	y = drag_vel.y;
}

bool Gui::IsMovable() const
{
	return movable;
}

void Gui::SetVisible(bool visible)
{
	this->visible = visible;
}

void Gui::SetOpacity(uint alpha)
{
	if ((alpha >= 0) && (alpha <= 255))
		opacity = alpha;
}

int Gui::GetOpacity() const
{
	return opacity;
}

void Gui::GainOpacityOverTime(uint initialalpha, uint finalalpha, uint transitionmilisec)
{
	//Waiting to be implemented when gui elements are implemented and working
}

void Gui::GainOpacityOverTime(uint finalalpha, uint transitionmilisec)
{
	//Waiting to be implemented when gui elements are implemented and working
}

void Gui::LossOpacityOverTime(uint initialalpha, uint finalalpha, uint transitionmilisec)
{
	//Waiting to be implemented when gui elements are implemented and working
}

void Gui::LossOpacityOverTime(uint finalalpha, uint transitionmilisec)
{
	//Waiting to be implemented when gui elements are implemented and working
}

void Gui::Focusable(bool value)
{
	can_focus = value;
}

bool Gui::FocusableStat() const
{
	return can_focus;
}

AddGuiTo Gui::GetPurpose() const
{
	return purpose;
}

bool Gui::InFOV()
{
	return ((visible == true) &&
		(((Gui_Collider.x >= -App->render->camera.x) && (Gui_Collider.x < (-App->render->camera.x + App->render->camera.w)) && (Gui_Collider.y >= -App->render->camera.y) && (Gui_Collider.y < (-App->render->camera.y + App->render->camera.h))) ||
		(((Gui_Collider.x + Gui_Collider.w) >= -App->render->camera.x) && ((Gui_Collider.x + Gui_Collider.w) < (-App->render->camera.x + App->render->camera.w)) && ((Gui_Collider.y + Gui_Collider.h) >= -App->render->camera.y) && ((Gui_Collider.y + Gui_Collider.h) < (-App->render->camera.y + App->render->camera.h)))));
}

bool Gui::PointContained(int x, int y) const
{
	return ((visible == true) &&
		((x >= Gui_Collider.x) && (x < (Gui_Collider.x + Gui_Collider.w)) &&
		(y >= Gui_Collider.y) && (y < (Gui_Collider.y + Gui_Collider.h))));
}

void Gui::CheckInput(const Gui* mouse_hover, const Gui* focus)
{
	if((mouse_hover == nullptr) && (focus == nullptr))
		return;

	bool inside = (mouse_hover == this);

	j1Module* listener = nullptr;

	if (module_listener != nullptr)
		listener = module_listener;
	if (scene_listener != nullptr)
		listener = (j1Module*)scene_listener;

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			if (module_listener != nullptr)
				listener->OnGui(this, (inside) ? GuiEvent::mouse_enter : GuiEvent::mouse_leave);
			else
				((MainScene*)listener)->OnGui(this, (inside) ? GuiEvent::mouse_enter : GuiEvent::mouse_leave);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_lclk_down);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_down);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_lclk_repeat);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_repeat);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_UP)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_lclk_up);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_up);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_DOWN)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_rclk_down);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_rclk_down);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_REPEAT)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_rclk_repeat);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_rclk_repeat);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_UP)
				if (module_listener != nullptr)
					listener->OnGui(this, GuiEvent::mouse_rclk_up);
				else
					((MainScene*)listener)->OnGui(this, GuiEvent::mouse_rclk_up);
		}

		if (drag_vel.x != 0.0f || drag_vel.y != 0.0f)
		{
			iPoint drag_event_mov = { 0, 0 };
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
				App->input->GetMouseMotion(drag_event_mov.x, drag_event_mov.y);
			if ((drag_event_mov.x != 0) || (drag_event_mov.y != 0))
			{
				iPoint p = GetLocalPos();
				SetLocalPos(p.x + int(drag_event_mov.x * drag_vel.x), p.y + int(drag_event_mov.y * drag_vel.y));
			}
		}
	}

	if (focus == this && listener != nullptr)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_DOWN)
			if (module_listener != nullptr)
				listener->OnGui(this, GuiEvent::mouse_lclk_down);
			else
				((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_down);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_REPEAT)
			if (module_listener != nullptr)
				listener->OnGui(this, GuiEvent::mouse_lclk_repeat);
			else
				((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_repeat);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_UP)
			if (module_listener != nullptr)
				listener->OnGui(this, GuiEvent::mouse_lclk_up);
			else
				((MainScene*)listener)->OnGui(this, GuiEvent::mouse_lclk_up);
	}
}

void Gui::SetListener(j1Module* module)
{
	module_listener = module;
}

void Gui::SetListener(MainScene* module)
{
	scene_listener = module;
}

const j1Module* Gui::GetModuleListener() const
{
	return module_listener;
}

const MainScene* Gui::GetSceneListener() const
{
	return scene_listener;
}