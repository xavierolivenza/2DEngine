#include "j1Gui.h"
#include "GuiCheck.h"

GuiCheck::GuiCheck(char* elementname, bool stat, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_check, movable, can_focus, move_with_camera, module_listener, addto), stat(stat)
{
	CommonConstructor(position, &std::string(elementname));
}

GuiCheck::GuiCheck(char* elementname, bool stat, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_check, movable, can_focus, move_with_camera, scene_listener, addto), stat(stat)
{
	CommonConstructor(position, &std::string(elementname));
}

void GuiCheck::CommonConstructor(iPoint position, std::string* elementname)
{
	atlas_check* CheckType = (atlas_check*)App->gui->GetAtlasPrefab(atlas_element_type::enum_atlas_check, elementname);
	if (CheckType != nullptr)
	{
		check_unchecked_background_Animation.loop = CheckType->check_unchecked_background->animation_loop;
		check_unchecked_background_Animation.frameMiliseconds = CheckType->check_unchecked_background->frameMiliseconds;
		check_unchecked_background_Animation.frames = CheckType->check_unchecked_background->atlas_element_state_frames;
		if ((CheckType->check_checked_background != nullptr) && (CheckType->check_check))
		{
			check_checked_background_Animation.loop = CheckType->check_checked_background->animation_loop;
			check_checked_background_Animation.frameMiliseconds = CheckType->check_checked_background->frameMiliseconds;
			check_checked_background_Animation.frames = CheckType->check_checked_background->atlas_element_state_frames;
			check_check_Animation.loop = CheckType->check_check->animation_loop;
			check_check_Animation.frameMiliseconds = CheckType->check_check->frameMiliseconds;
			check_check_Animation.frames = CheckType->check_check->atlas_element_state_frames;
			threeTex = true;
		}
		else
		{
			check_checked_backed_check_Animation.loop = CheckType->check_checked_backed_check->animation_loop;
			check_checked_backed_check_Animation.frameMiliseconds = CheckType->check_checked_backed_check->frameMiliseconds;
			check_checked_backed_check_Animation.frames = CheckType->check_checked_backed_check->atlas_element_state_frames;
			threeTex = false;
		}
		Atlas = CheckType->Atlas_texture;
		ActualCheckAnimation = &check_unchecked_background_Animation;
		Gui_Collider = { position.x - CheckType->Collider.x,position.y - CheckType->Collider.y,CheckType->Collider.w,CheckType->Collider.h };
	}
	else
		LOG("Error Loading Check %s", elementname->c_str());
}

GuiCheck::~GuiCheck()
{

}

void GuiCheck::Update(const Gui* mouse_hover, const Gui* focus)
{
	bool inside = (mouse_hover == (Gui*)this);

	if ((inside == true) && (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN))
	{
		stat = !stat;
		if (stat)
		{
			if(threeTex)
				ActualCheckAnimation = &check_checked_background_Animation;
			else
				ActualCheckAnimation = &check_checked_backed_check_Animation;
		}
		else
			ActualCheckAnimation = &check_unchecked_background_Animation;
	}
}

void GuiCheck::Draw()
{
	if (this->visible)
	{
		Frame actualFrame = ActualCheckAnimation->GetCurrentFrame();

		if (this->move_with_camera)
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		else
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		
		if (threeTex && stat)
		{
			actualFrame = check_check_Animation.GetCurrentFrame();
			if (this->move_with_camera)
				App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
			else
				App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		}

		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiCheck::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, GuiCheckDebugColor(0), GuiCheckDebugColor(1), GuiCheckDebugColor(2), DEBUG_DRAW_ALPHA, true, false, false);
}

bool GuiCheck::Stat() const
{
	return stat;
}
/*
void GuiCheck::ChangeState()
{
	checked = !checked;
	if (checked)
		curent_state_texture = &pressed_texture_rect;
	else
		curent_state_texture = &idle_texture_rect;
}
*/