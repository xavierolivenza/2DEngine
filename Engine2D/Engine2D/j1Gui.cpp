#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1FileSystem.h"
#include "j1Scene.h"
#include "GuiXMLStorage.h"
#include "j1Console.h"

#include "GuiImage.h"
#include "GuiLabel.h"
#include "GuiInputText.h"
#include "GuiButton.h"
#include "GuiWindow.h"
#include "GuiCheck.h"

//Just an example of how multimap work, just in case that i need it
/*
for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
	if ((*item).second == atlas)
return (*item).first;
*/
/*
std::pair<SDL_Texture*, GUIAtlas> new_atlas;
new_atlas.first = App->tex->Load(default_atlas_file_name.c_str());
new_atlas.second = GUIAtlas::default;
atlas_multimap.insert(new_atlas);
*/
/*
for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
	App->tex->UnLoad((*item).first);
atlas_multimap.clear();
*/

j1Gui::j1Gui() : j1Module()
{
	name = "gui";
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	PushBackNewAtlas(conf.child("default_atlas"), GUIAtlas::default);
	PushBackNewAtlas(conf.child("over_atlas"), GUIAtlas::over);
	PushBackNewAtlas(conf.child("fire_atlas"), GUIAtlas::fire);

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	LOG("Loading Gui Atlas");
	for (std::list<Atlas*>::iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
	{
		(item._Ptr->_Myval)->texture = App->tex->Load((item._Ptr->_Myval)->atlas_file_name.c_str());
		(item._Ptr->_Myval)->atlas_content = LoadAtlasRectsXML(&(item._Ptr->_Myval)->atlas_rects_file_name, (item._Ptr->_Myval)->texture);
	}

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		Gui_DebugDraw = !Gui_DebugDraw;
	return true;
}

// Called each loop iteration
bool j1Gui::Update(float dt)
{
	// Draw all guis
	for (std::list<Gui*>::iterator item = GuiElements.begin(); item != GuiElements.cend(); ++item)
		if ((item._Ptr->_Myval)->GetPurpose() != AddGuiTo::viewport_purpose)
		{
			if(((item._Ptr->_Myval)->ParentWindow == nullptr) || (((item._Ptr->_Myval)->ParentWindow != nullptr) && ((item._Ptr->_Myval)->ParentWindow->visible)))
			{
				if ((item._Ptr->_Myval)->GetModuleListener() != nullptr)
					(item._Ptr->_Myval)->Draw();
				if ((item._Ptr->_Myval)->GetSceneListener() != nullptr)//if is scene
					if ((item._Ptr->_Myval)->GetSceneListener() == App->scene->GetActiveScene())
						(item._Ptr->_Myval)->Draw();
			}
		}
	if (App->console->IsActive())
	{
		/*
		App->render->DrawQuad(App->console->ConsoleBackground, Black(0), Black(1), Black(2), CONSOLE_ALPHA, true, true, false);
		App->render->DrawQuad(App->console->ConsoleInputTextBackground, Gray(0), Gray(1), Gray(2), CONSOLE_ALPHA, true, true, false);
		for (std::list<Gui*>::iterator item = ConsoleElements.begin(); item != ConsoleElements.cend(); ++item)
		{
			if ((*item)->type == GuiType::gui_label)// && (InFOV(*item)
				if ((*item)->type == GuiType::gui_label)
				{
					SDL_Rect ViewportRect = { 0,0,App->console->ConsoleBackground.w,App->console->ConsoleBackground.h };
					SDL_RenderSetViewport(App->render->renderer, &ViewportRect);
					(*item)->Draw();
					SDL_RenderSetViewport(App->render->renderer, NULL);
				}
			if ((*item)->type == GuiType::gui_inputtext)
				(*item)->Draw();
		}
		*/
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	// Update all guis
	std::list<Gui*>* list_to_iterate = nullptr;
	if (App->console->IsActive())
		list_to_iterate = &ConsoleElements;
	else
		list_to_iterate = &GuiElements;

	const Gui* mouse_hover = FindMouseHover();
	if (mouse_hover && mouse_hover->can_focus == true)
		if (mouse_hover->GetSceneListener() == App->scene->GetActiveScene())
			SetFocus(mouse_hover);

	if (mouse_hover && mouse_hover->can_focus == true && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN)
		SetFocus(mouse_hover);

	iPoint newCameraPos = { App->render->camera.x,App->render->camera.y };
	bool cam_moved = false;
	if (cameraPos != newCameraPos)
		cam_moved = true;

	for (std::list<Gui*>::iterator item = list_to_iterate->begin(); item != list_to_iterate->cend(); ++item)
	{
		if ((item._Ptr->_Myval)->movable && !(item._Ptr->_Myval)->move_with_camera)
			if (cam_moved)
			{
				(item._Ptr->_Myval)->Gui_Collider.x += (newCameraPos.x - cameraPos.x);
				(item._Ptr->_Myval)->Gui_Collider.y += (newCameraPos.y - cameraPos.y);
			}
		if (((item._Ptr->_Myval)->ParentWindow == nullptr) || (((item._Ptr->_Myval)->ParentWindow != nullptr) && ((item._Ptr->_Myval)->ParentWindow->visible)))
		{
			if ((item._Ptr->_Myval)->GetModuleListener() != nullptr)
			{
				(item._Ptr->_Myval)->CheckInput(mouse_hover, focus);
				(item._Ptr->_Myval)->Update(mouse_hover, focus);
			}
			if ((item._Ptr->_Myval)->GetSceneListener() != nullptr)//if is scene
				if ((item._Ptr->_Myval)->GetSceneListener() == App->scene->GetActiveScene())
				{
					(item._Ptr->_Myval)->CheckInput(mouse_hover, focus);
					(item._Ptr->_Myval)->Update(mouse_hover, focus);
				}
		}
		if (App->console->IsActive())
		{
			(item._Ptr->_Myval)->CheckInput(mouse_hover, focus);
			(item._Ptr->_Myval)->Update(mouse_hover, focus);
		}
	}
	
	cameraPos = newCameraPos;

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (std::list<Atlas*>::iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
	{
		if ((item._Ptr->_Myval)->texture != nullptr)
			App->tex->UnLoad((item._Ptr->_Myval)->texture);
		if ((item._Ptr->_Myval)->atlas_content != nullptr)
		{
			for (std::list<atlas_element*>::iterator item2 = ((item._Ptr->_Myval)->atlas_content)->begin(); item2 != ((item._Ptr->_Myval)->atlas_content)->cend(); ++item2)
			{
				switch (item2._Ptr->_Myval->type)
				{
				case atlas_element_type::enum_atlas_image:
				case atlas_element_type::enum_atlas_label:
				case atlas_element_type::enum_atlas_window:
					break;
				case atlas_element_type::enum_atlas_button:
					RELEASE(((atlas_button*)item2._Ptr->_Myval)->state_idle);
					RELEASE(((atlas_button*)item2._Ptr->_Myval)->state_hover);
					RELEASE(((atlas_button*)item2._Ptr->_Myval)->state_pressed);
					break;
				case atlas_element_type::enum_atlas_scrollbar_vertical:
				case atlas_element_type::enum_atlas_scrollbar_horitzontal:
					RELEASE(((atlas_scrollbar*)item2._Ptr->_Myval)->scrollbar_background);
					RELEASE(((atlas_scrollbar*)item2._Ptr->_Myval)->scrollbar_line);
					RELEASE(((atlas_button*)((atlas_scrollbar*)item2._Ptr->_Myval)->scrollbar_button)->state_idle);
					RELEASE(((atlas_button*)((atlas_scrollbar*)item2._Ptr->_Myval)->scrollbar_button)->state_hover);
					RELEASE(((atlas_button*)((atlas_scrollbar*)item2._Ptr->_Myval)->scrollbar_button)->state_pressed);
					RELEASE(((atlas_scrollbar*)item2._Ptr->_Myval)->scrollbar_button);
					break;
				case atlas_element_type::enum_atlas_check:
					RELEASE(((atlas_check*)item2._Ptr->_Myval)->check_unchecked_background);
					RELEASE(((atlas_check*)item2._Ptr->_Myval)->check_checked_background);
					RELEASE(((atlas_check*)item2._Ptr->_Myval)->check_check);
					RELEASE(((atlas_check*)item2._Ptr->_Myval)->check_checked_backed_check);
					break;
				default:
					break;
				}
				RELEASE((item2._Ptr->_Myval));
			}
			RELEASE((item._Ptr->_Myval)->atlas_content);
		}
		RELEASE((item._Ptr->_Myval));
	}
	gui_atlas_list.clear();

	for (std::list<Gui*>::iterator item = GuiElements.begin(); item != GuiElements.cend(); ++item)
		RELEASE(item._Ptr->_Myval);
	GuiElements.clear();

	for (std::list<Gui*>::iterator item = ConsoleElements.begin(); item != ConsoleElements.cend(); ++item)
		RELEASE(item._Ptr->_Myval);
	ConsoleElements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas(GUIAtlas atlas) const
{
	for (std::list<Atlas*>::const_iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
		if (item._Ptr->_Myval->atlas_type == atlas)
			return item._Ptr->_Myval->texture;

	return nullptr;
}

void j1Gui::PushBackNewAtlas(pugi::xml_node& conf, GUIAtlas AtalsEnum)
{
	gui_atlas_list.push_back(new Atlas(conf.attribute("texture").as_string(""), conf.attribute("rects").as_string(""), AtalsEnum));
}

std::list<atlas_element*>* j1Gui::LoadAtlasRectsXML(std::string* file, SDL_Texture* atlas_texture)
{
	std::list<atlas_element*>* temp = nullptr;

	LOG("Loading XML file %s", file->c_str());

	pugi::xml_document	config_file;
	pugi::xml_node		atlas_config;

	char* buffer = nullptr;
	int size = App->fs->Load(file->c_str(), &buffer);
	pugi::xml_parse_result result = config_file.load_buffer(buffer, size);
	RELEASE(buffer);

	if (result == NULL)
		LOG("Could not load XML file %s. pugi error: %s", file->c_str(), result.description());
	else
		atlas_config = config_file.child("gui_atlas_rects");

	if (!atlas_config.empty())
	{
		temp = new std::list<atlas_element*>;

		//Iterate all images stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Image").child("image"); newimage; newimage = newimage.next_sibling("image"))
		{
			temp->push_back(AllocateNewImageLabelWindow(newimage, atlas_element_type::enum_atlas_image, atlas_texture));
		}

		//Iterate all labels stored in XML file
		for (pugi::xml_node newlabel = atlas_config.child("GUI_Label").child("label"); newlabel; newlabel = newlabel.next_sibling("label"))
		{
			temp->push_back(AllocateNewImageLabelWindow(newlabel, atlas_element_type::enum_atlas_label, atlas_texture));
		}

		//Iterate all windows stored in XML file
		for (pugi::xml_node newwindow = atlas_config.child("GUI_Window").child("window"); newwindow; newwindow = newwindow.next_sibling("window"))
		{
			temp->push_back(AllocateNewImageLabelWindow(newwindow, atlas_element_type::enum_atlas_window, atlas_texture));
		}

		//Iterate all buttons stored in XML file
		for (pugi::xml_node newbutton = atlas_config.child("GUI_Button").child("button"); newbutton; newbutton = newbutton.next_sibling("button"))
		{
			temp->push_back(AllocateNewButton(newbutton, atlas_texture));
		}

		//Iterate all vertical scrollbars stored in XML file
		for (pugi::xml_node newverticalscrollbar = atlas_config.child("GUI_Scrollbar_Vertical").child("scrollbar_vertical"); newverticalscrollbar; newverticalscrollbar = newverticalscrollbar.next_sibling("scrollbar_vertical"))
		{
			temp->push_back(AllocateNewScrollbar(newverticalscrollbar, atlas_element_type::enum_atlas_scrollbar_vertical, atlas_texture));
		}

		//Iterate all horitzontal scrollbars stored in XML file
		for (pugi::xml_node newhoritzontalscrollbar = atlas_config.child("GUI_Scrollbar_Horitzontal").child("scrollbar_horitzontal"); newhoritzontalscrollbar; newhoritzontalscrollbar = newhoritzontalscrollbar.next_sibling("scrollbar_horitzontal"))
		{
			temp->push_back(AllocateNewScrollbar(newhoritzontalscrollbar, atlas_element_type::enum_atlas_scrollbar_horitzontal, atlas_texture));
		}

		//Iterate all checks stored in XML file
		for (pugi::xml_node newcheck = atlas_config.child("GUI_Check").child("check"); newcheck; newcheck = newcheck.next_sibling("check"))
		{
			temp->push_back(AllocateNewCheck(newcheck, atlas_texture));
		}
	}
	return temp;
}

atlas_image_label_window* j1Gui::AllocateNewImageLabelWindow(pugi::xml_node& NewImageLabelWindow, atlas_element_type type, SDL_Texture* atlas_texture)
{
	if ((type != atlas_element_type::enum_atlas_image) && (type != atlas_element_type::enum_atlas_label) && (type != atlas_element_type::enum_atlas_window))
		return nullptr;

	std::vector<Frame> atlas_element_state_frames;
	for (pugi::xml_node newstate = NewImageLabelWindow.child("state"); newstate; newstate = newstate.next_sibling("state"))
	{
		Frame newframe;
		newframe.rect = { newstate.attribute("x").as_int(0),newstate.attribute("y").as_int(0),newstate.attribute("w").as_int(0),newstate.attribute("h").as_int(0) };
		newframe.pivot = { newstate.attribute("pivot_x").as_int(0),newstate.attribute("pivot_y").as_int(0) };
		atlas_element_state_frames.push_back(newframe);
	}

	//this is usefull for thing like the Checkbox which you have the option of making it in two ways, or buttons with less than 3 states.
	//1. With check_unchecked_background, check_checked_background and check_check.
	//2. With check_unchecked_background and check_checked_backed_check.
	//So from code is usefull to know if some image is in fact null
	/*
	if (((char*)NewImageLabelWindow.attribute("name").as_string("") == "") && !NewImageLabelWindow.attribute("animation_loop").as_bool(false) &&
		(NewImageLabelWindow.attribute("animation_speed").as_float(0.0f) == 0.0f) && atlas_element_state_frames.empty())
		return nullptr;
	*/
	if (atlas_element_state_frames.empty())
		return nullptr;

	SDL_Rect collider = { NewImageLabelWindow.child("collider").attribute("x").as_int(0),NewImageLabelWindow.child("collider").attribute("y").as_int(0),
		NewImageLabelWindow.child("collider").attribute("w").as_int(0) ,NewImageLabelWindow.child("collider").attribute("h").as_int(0) };
	
	atlas_image_label_window* newtoadd = new atlas_image_label_window((char*)NewImageLabelWindow.attribute("name").as_string(""),
		type, NewImageLabelWindow.attribute("animation_loop").as_bool(false), NewImageLabelWindow.attribute("frameMiliseconds").as_int(0),
		&atlas_element_state_frames, &collider, atlas_texture);

	return newtoadd;
}

atlas_button* j1Gui::AllocateNewButton(pugi::xml_node& NewButton, SDL_Texture* atlas_texture)
{
	atlas_image_label_window* state_idle = AllocateNewImageLabelWindow(NewButton.child("state_idle"), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_image_label_window* state_hover = AllocateNewImageLabelWindow(NewButton.child("state_hover"), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_image_label_window* state_pressed = AllocateNewImageLabelWindow(NewButton.child("state_pressed"), atlas_element_type::enum_atlas_image, atlas_texture);

	SDL_Rect collider = { NewButton.child("collider").attribute("x").as_int(0),NewButton.child("collider").attribute("y").as_int(0),
		NewButton.child("collider").attribute("w").as_int(0) ,NewButton.child("collider").attribute("h").as_int(0) };

	atlas_button* newbuttontoadd = new atlas_button((char*)NewButton.attribute("name").as_string(""), atlas_element_type::enum_atlas_button, state_idle,
		state_hover, state_pressed, &collider, atlas_texture);
	return newbuttontoadd;
}

atlas_check* j1Gui::AllocateNewCheck(pugi::xml_node& NewCheck, SDL_Texture* atlas_texture)
{
	atlas_image_label_window* check_unchecked_background = AllocateNewImageLabelWindow(NewCheck.child("check_unchecked_background"), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_image_label_window* check_checked_background = AllocateNewImageLabelWindow(NewCheck.child("check_checked_background"), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_image_label_window* check_check = AllocateNewImageLabelWindow(NewCheck.child("check_check"), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_image_label_window* check_checked_backed_check = AllocateNewImageLabelWindow(NewCheck.child("check_checked_backed_check"), atlas_element_type::enum_atlas_image, atlas_texture);

	SDL_Rect collider = { NewCheck.child("collider").attribute("x").as_int(0),NewCheck.child("collider").attribute("y").as_int(0),
		NewCheck.child("collider").attribute("w").as_int(0) ,NewCheck.child("collider").attribute("h").as_int(0) };

	atlas_check* newchecktoadd = new atlas_check((char*)NewCheck.attribute("name").as_string(""), atlas_element_type::enum_atlas_check, check_unchecked_background,
		check_checked_background, check_check, check_checked_backed_check, &collider, atlas_texture);
	return newchecktoadd;
}

atlas_scrollbar* j1Gui::AllocateNewScrollbar(pugi::xml_node& NewScrollbar, atlas_element_type type, SDL_Texture* atlas_texture)
{
	if ((type != atlas_element_type::enum_atlas_scrollbar_vertical) && (type != atlas_element_type::enum_atlas_scrollbar_horitzontal))
		return nullptr;

	char* scrollbar_background_str = "scrollbar_vertical_background";
	char* scrollbar_line_str = "scrollbar_vertical_line";
	char* scrollbar_button_str = "scrollbar_vertical_button";

	if (type == atlas_element_type::enum_atlas_scrollbar_horitzontal)
	{
		scrollbar_background_str = "scrollbar_horitzontal_background";
		scrollbar_line_str = "scrollbar_horitzontal_line";
		scrollbar_button_str = "scrollbar_horitzontal_button";
	}

	atlas_image_label_window* scrollbar_background = AllocateNewImageLabelWindow(NewScrollbar.child(scrollbar_background_str), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_image_label_window* scrollbar_line = AllocateNewImageLabelWindow(NewScrollbar.child(scrollbar_line_str), atlas_element_type::enum_atlas_image, atlas_texture);
	atlas_button* scrollbar_button = AllocateNewButton(NewScrollbar.child(scrollbar_button_str), atlas_texture);

	SDL_Rect collider = { NewScrollbar.child("collider").attribute("x").as_int(0),NewScrollbar.child("collider").attribute("y").as_int(0),
		NewScrollbar.child("collider").attribute("w").as_int(0) ,NewScrollbar.child("collider").attribute("h").as_int(0) };

	atlas_scrollbar* newscrollbartoadd = new atlas_scrollbar((char*)NewScrollbar.attribute("name").as_string(""), type,
		scrollbar_background, scrollbar_line, scrollbar_button, &collider, atlas_texture);
	return newscrollbartoadd;
}

const atlas_element* j1Gui::GetAtlasPrefab(atlas_element_type type, std::string* name) const
{
	if ((name != nullptr) && (name != &std::string("")))
		for (std::list<Atlas*>::const_iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
			if ((item._Ptr->_Myval)->atlas_content != nullptr)
				for (std::list<atlas_element*>::iterator item2 = ((item._Ptr->_Myval)->atlas_content)->begin(); item2 != ((item._Ptr->_Myval)->atlas_content)->cend(); ++item2)
					if ((item2._Ptr->_Myval)->type == type)
						if ((item2._Ptr->_Myval)->name == *name)
							return item2._Ptr->_Myval;
	return nullptr;
}

void j1Gui::SetFocus(const Gui* ui)
{
	j1Module* listener = nullptr;

	if (ui != focus)
	{
		if (ui != nullptr)
		{
			if (ui->module_listener != nullptr)
				listener = ui->module_listener;
			if (ui->scene_listener != nullptr)
				listener = (j1Module*)ui->scene_listener;
			//if (ui->can_focus == true && CanInteract(ui) == true)
			if (ui->can_focus && (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN))
			{
				if (focus != nullptr)
				{
					if (ui->module_listener != nullptr)
						listener->OnGui(focus, GuiEvent::lost_focus);
					else
						((MainScene*)listener)->OnGui(focus, GuiEvent::lost_focus);
					focus->FocusLost();
				}
				focus = (Gui*)ui;
				if (ui->module_listener != nullptr)
					listener->OnGui(focus, GuiEvent::gain_focus);
				else
					((MainScene*)listener)->OnGui(focus, GuiEvent::gain_focus);
				focus->FocusGained();
			}
		}
		else
		{
			if (focus != nullptr)
			{
				if (ui != nullptr)
				{
					if (ui->module_listener != nullptr)
						ui->module_listener->OnGui(focus, GuiEvent::lost_focus);
					else
						((MainScene*)ui->scene_listener)->OnGui(focus, GuiEvent::lost_focus);
				}
			}
			focus = nullptr;
		}
	}
}

const Gui* j1Gui::GetFocus() const
{
	return focus;
}

bool j1Gui::isDebugDrawActive() const
{
	return Gui_DebugDraw;
}

const Gui* j1Gui::FindMouseHover()
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	std::list<Gui*>* list_to_iterate = nullptr;
	if (App->console->IsActive())
		list_to_iterate = &ConsoleElements;
	else
		list_to_iterate = &GuiElements;

	for (std::list<Gui*>::const_reverse_iterator item = list_to_iterate->rbegin(); item != list_to_iterate->crend(); ++item)
	{
		if ((list_to_iterate == &ConsoleElements) && ((*item)->type == GuiType::gui_label))
			continue;
		else
			if (CanInteract(*item) == true)
				if ((*item)->PointContained(mouse.x, mouse.y))
					return *item;
		/*
		if ((*item)->InFOV())
		{
		if ((list_to_iterate == &ConsoleElements) && ((*item)->type == GuiType::gui_label))
		continue;
		else
		if (CanInteract(*item) == true)
		if ((*item)->PointContained(mouse.x, mouse.y))
		return *item;
		}
		*/
	}

	return nullptr;
}

bool j1Gui::CanInteract(const Gui* ui) const
{
	bool inscene = false;
	if (((ui->module_listener != nullptr) && (ui->module_listener->active)) || ((ui->scene_listener != nullptr) && (ui->scene_listener == App->scene->GetActiveScene())))
		inscene = true;
	return ui->visible && inscene;
	//return ui->movable && ui->visible;
}

void j1Gui::push_back_gui(Gui* gui, AddGuiTo addto)
{
	switch (addto)
	{
	case AddGuiTo::regular_purpose:
	case AddGuiTo::window_purpose:
		GuiElements.push_back(gui);
		break;
	case AddGuiTo::console_purpose:
		ConsoleElements.push_back(gui);
		break;
	case AddGuiTo::null_AddGuiTo:
	case AddGuiTo::viewport_purpose:
		break;
	}
}

GuiImage* j1Gui::CreateImage(char* elementname, iPoint position, j1Module* module_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiImage* ret = nullptr;
	ret = new GuiImage(elementname, position, movable, can_focus, move_with_camera, module_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiImage* j1Gui::CreateImage(char* elementname, iPoint position, MainScene* scene_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiImage* ret = nullptr;
	ret = new GuiImage(elementname, position, movable, can_focus, move_with_camera, scene_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiLabel* j1Gui::CreateLabel(char* str, char* elementname, iPoint position, j1Module* module_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiLabel* ret = nullptr;
	ret = new GuiLabel(str, elementname, position, movable, can_focus, move_with_camera, module_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiLabel* j1Gui::CreateLabel(char* str, char* elementname, iPoint position, MainScene* scene_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiLabel* ret = nullptr;
	ret = new GuiLabel(str, elementname, position, movable, can_focus, move_with_camera, scene_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiInputText* j1Gui::CreateGuiInputText(char* str, char* elementname, iPoint position, j1Module* module_listener, bool isPassword, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiInputText* ret = nullptr;
	ret = new GuiInputText(str, elementname, position, isPassword, movable, can_focus, move_with_camera, module_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiInputText* j1Gui::CreateGuiInputText(char* str, char* elementname, iPoint position, MainScene* scene_listener, bool isPassword, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiInputText* ret = nullptr;
	ret = new GuiInputText(str, elementname, position, isPassword, movable, can_focus, move_with_camera, scene_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiButton* j1Gui::CreateButton(char* str, ButtonType type, char* elementname, iPoint position, j1Module* module_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiButton* ret = nullptr;
	ret = new GuiButton(str, type, elementname, position, movable, can_focus, move_with_camera, module_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiButton* j1Gui::CreateButton(char* str, ButtonType type, char* elementname, iPoint position, MainScene* scene_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiButton* ret = nullptr;
	ret = new GuiButton(str, type, elementname, position, movable, can_focus, move_with_camera, scene_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiWindow* j1Gui::CreateGuiWindow(char* elementname, iPoint position, j1Module* module_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiWindow* ret = nullptr;
	ret = new GuiWindow(elementname, position, movable, can_focus, move_with_camera, module_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiWindow* j1Gui::CreateGuiWindow(char* elementname, iPoint position, MainScene* scene_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiWindow* ret = nullptr;
	ret = new GuiWindow(elementname, position, movable, can_focus, move_with_camera, scene_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiCheck* j1Gui::CreateCheck(char* elementname, bool stat, iPoint position, j1Module* module_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiCheck* ret = nullptr;
	ret = new GuiCheck(elementname, stat, position, movable, can_focus, move_with_camera, module_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}

GuiCheck* j1Gui::CreateCheck(char* elementname, bool stat, iPoint position, MainScene* scene_listener, bool movable, bool can_focus, bool move_with_camera, AddGuiTo addto)
{
	GuiCheck* ret = nullptr;
	ret = new GuiCheck(elementname, stat, position, movable, can_focus, move_with_camera, scene_listener, addto);
	push_back_gui(ret, addto);
	return ret;
}