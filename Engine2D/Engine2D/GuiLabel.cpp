#include "GuiLabel.h"
#include "j1Gui.h"

GuiLabel::GuiLabel(char* str, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_label, movable, can_focus, move_with_camera, module_listener, addto)
{
	CommonConstructor(position, &std::string(str), &std::string(elementname));
}

GuiLabel::GuiLabel(char* str, char* elementname, iPoint position, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_label, movable, can_focus, move_with_camera, scene_listener, addto)
{
	CommonConstructor(position, &std::string(str), &std::string(elementname));
}

void GuiLabel::CommonConstructor(iPoint position, std::string* str, std::string* elementname)
{
	if (str != &std::string(""))
	{
		atlas_image_label_window* LabelType = (atlas_image_label_window*)App->gui->GetAtlasPrefab(atlas_element_type::enum_atlas_label, elementname);
		if (LabelType != nullptr)
		{
			LabelBackgroundAnimation.loop = LabelType->animation_loop;
			LabelBackgroundAnimation.frameMiliseconds = LabelType->frameMiliseconds;
			LabelBackgroundAnimation.frames = LabelType->atlas_element_state_frames;
			Atlas = LabelType->Atlas_texture;
			Gui_Collider = { position.x - LabelType->Collider.x,position.y - LabelType->Collider.y,LabelType->Collider.w,LabelType->Collider.h };
			hasBackground = true;
		}
		else
			LOG("Error Loading Label %s", elementname->c_str());
		this->str = *str;
	}
}

GuiLabel::~GuiLabel()
{
	
}

void GuiLabel::Draw()
{
	if (this->visible)
	{
		//Blit background if it was assigned in the constructor
		if(hasBackground)
		{
			Frame actualFrame = LabelBackgroundAnimation.GetCurrentFrame();
			if (this->move_with_camera)
				App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
			else
				App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		}
		//Blit label itself

		
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiLabel::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, GuiLabelDebugColor(0), GuiLabelDebugColor(1), GuiLabelDebugColor(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiLabel::SetAnimationFrameMiliseconds(int frameMiliseconds)
{
	if (hasBackground)
		LabelBackgroundAnimation.frameMiliseconds = frameMiliseconds;
}