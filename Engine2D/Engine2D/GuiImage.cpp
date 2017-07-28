#include "GuiImage.h"
#include "j1Gui.h"

GuiImage::GuiImage(char* elementname, iPoint position, bool movable, bool move_with_camera, bool can_focus, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_image, movable, can_focus, move_with_camera, module_listener, addto)
{
	CommonConstructor(&std::string(elementname));
}

GuiImage::GuiImage(char* elementname, iPoint position, bool movable, bool move_with_camera, bool can_focus, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_image, movable, can_focus, move_with_camera, scene_listener, addto)
{
	CommonConstructor(&std::string(elementname));
}

void GuiImage::CommonConstructor(std::string* elementname)
{
	atlas_image_label_window* ImageType = (atlas_image_label_window*)App->gui->GetAtlasPrefab(atlas_element_type::enum_atlas_image, elementname);
	ImageAnimation.loop = ImageType->animation_loop;
	ImageAnimation.speed = ImageType->animation_speed;
	ImageAnimation.frames = ImageType->atlas_element_state_frames;
	Atlas = ImageType->Atlas_texture;
	Gui_Collider = ImageType->Collider;
}

GuiImage::~GuiImage()
{
	
}

void GuiImage::Draw()
{
	if (this->visible)
	{
		Frame actualFrame = ImageAnimation.GetCurrentFrame();

		if (this->move_with_camera)
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x - App->render->camera.x, position.y - actualFrame.pivot.y - App->render->camera.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		else
			App->render->Blit(Atlas, position.x, position.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiImage::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Lime(0), Lime(1), Lime(2), DEBUG_DRAW_ALPHA, true, false, false);
}