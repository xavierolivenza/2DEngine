#include "GuiImage.h"

GuiImage::GuiImage(char* elementname, iPoint position, bool movable, bool can_focus, j1Module* module_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_image, movable, can_focus, module_listener, addto)
{
	CommonConstructor(&std::string(elementname));
}

GuiImage::GuiImage(char* elementname, iPoint position, bool movable, bool can_focus, MainScene* scene_listener, AddGuiTo addto) :
	Gui(position, GuiType::gui_image, movable, can_focus, module_listener, addto)
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
}

GuiImage::~GuiImage()
{
	
}

void GuiImage::Draw()
{

}

void GuiImage::DebugDraw() const
{

}