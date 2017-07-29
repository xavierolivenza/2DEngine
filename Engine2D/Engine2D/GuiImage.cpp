#include "GuiImage.h"
#include "j1Gui.h"

GuiImage::GuiImage(char* elementname, iPoint position, bool movable, bool move_with_camera, bool can_focus, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_image, movable, can_focus, move_with_camera, module_listener, addto)
{
	CommonConstructor(position, &std::string(elementname));
}

GuiImage::GuiImage(char* elementname, iPoint position, bool movable, bool move_with_camera, bool can_focus, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_image, movable, can_focus, move_with_camera, scene_listener, addto)
{
	CommonConstructor(position, &std::string(elementname));
}

void GuiImage::CommonConstructor(iPoint position, std::string* elementname)
{
	atlas_image_label_window* ImageType = (atlas_image_label_window*)App->gui->GetAtlasPrefab(atlas_element_type::enum_atlas_image, elementname);
	ImageAnimation.loop = ImageType->animation_loop;
	ImageAnimation.frameMiliseconds = ImageType->frameMiliseconds;
	ImageAnimation.frames = ImageType->atlas_element_state_frames;
	Atlas = ImageType->Atlas_texture;
	Gui_Collider = { position.x - ImageType->Collider.x,position.y - ImageType->Collider.y,ImageType->Collider.w,ImageType->Collider.h };
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
			App->render->Blit(Atlas, position.x - actualFrame.pivot.x, position.y - actualFrame.pivot.y, &actualFrame.rect, 1.0f, 0, INT_MAX, INT_MAX);
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiImage::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, Lime(0), Lime(1), Lime(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiImage::SetAnimationFrameMiliseconds(int frameMiliseconds)
{
	ImageAnimation.frameMiliseconds = frameMiliseconds;
}