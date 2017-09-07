#include "GuiWindow.h"
#include "j1Gui.h"

GuiWindow::GuiWindow(char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_window, movable, can_focus, move_with_camera, module_listener, addto)
{
	CommonConstructor(position, &std::string(elementname));
}

GuiWindow::GuiWindow(char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_window, movable, can_focus, move_with_camera, scene_listener, addto)
{
	CommonConstructor(position, &std::string(elementname));
}

void GuiWindow::CommonConstructor(iPoint position, std::string* elementname)
{
	atlas_image_label_window* WindowType = (atlas_image_label_window*)App->gui->GetAtlasPrefab(atlas_element_type::enum_atlas_window, elementname);
	if (WindowType != nullptr)
	{
		WindowAnimation.loop = WindowType->animation_loop;
		WindowAnimation.frameMiliseconds = WindowType->frameMiliseconds;
		WindowAnimation.frames = WindowType->atlas_element_state_frames;
		Atlas = WindowType->Atlas_texture;
		Gui_Collider = { position.x - WindowType->Collider.x,position.y - WindowType->Collider.y,WindowType->Collider.w,WindowType->Collider.h };
	}
	else
		LOG("Error Loading Window %s", elementname->c_str());
}

GuiWindow::~GuiWindow()
{

}

void GuiWindow::Update(const Gui* mouse_hover, const Gui* focus)
{
	int i = 0;
}

void GuiWindow::Draw()
{
	if (this->visible)
	{
		Frame actualFrame = WindowAnimation.GetCurrentFrame();

		if (this->move_with_camera)
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		else
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiWindow::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, GuiWindowDebugColor(0), GuiWindowDebugColor(1), GuiWindowDebugColor(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiWindow::SetAnimationFrameMiliseconds(int frameMiliseconds)
{
	WindowAnimation.frameMiliseconds = frameMiliseconds;
}

void GuiWindow::push_back_item(Gui* newitem)
{

}

/*
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1Input.h"
#include "GuiWindow.h"

GuiWindow::GuiWindow(iPoint position, SDL_Rect* rect, bool has_background, bool movable, AddGuiTo addto) : Gui(position, GuiType::gui_window, movable, addto),
	background_rect(*rect), has_background(has_background)
{
	Gui_Collider = { position.x, position.y, rect->w, rect->h };
}

GuiWindow::~GuiWindow()
{
	//WindowElements is released in the general cleanup loop
}

void GuiWindow::Update(const Gui* mouse_hover, const Gui* focus)
{
	if (OriginalPosition != position)
	{
		iPoint drag_event_mov = { 0, 0 };
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
			App->input->GetMouseMotion(drag_event_mov.x, drag_event_mov.y);

		iPoint item_local_pos;
		fPoint item_drag_vel;
		for (std::list<Gui*>::iterator item = WindowElements.begin(); item != WindowElements.cend(); ++item)
		{
			item_drag_vel = (*item)->GetDragVelocity();
			if (item_drag_vel.x != 0.0f || item_drag_vel.y != 0.0f)
			{
				item_local_pos = (*item)->GetLocalPos();
				(*item)->SetLocalPos(item_local_pos.x + int(drag_event_mov.x * drag_vel.x), item_local_pos.y + int(drag_event_mov.y * drag_vel.y));
			}
		}
		OriginalPosition = position;
	}
}

void GuiWindow::Draw()
{
	if (this->visible == true)
	{
		if (has_background)
			App->render->Blit(App->gui->GetAtlas(), position.x - App->render->camera.x, position.y - App->render->camera.y, &background_rect, 1.0f, 0, INT_MAX, INT_MAX, false);
		if (App->gui->Gui_DebugDraw_isactive())
			this->DebugDraw();
	}
}

void GuiWindow::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, DarkBlue(0), DarkBlue(1), DarkBlue(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiWindow::push_back_item(Gui* newitem)
{
	WindowElements.push_back(newitem);
}
*/