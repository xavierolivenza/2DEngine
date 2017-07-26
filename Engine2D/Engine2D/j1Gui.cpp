#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1FileSystem.h"

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

	PushBackNewAtlas(conf, "default_atlas", "default_atlas_rects", GUIAtlas::default);
	PushBackNewAtlas(conf, "over_atlas", "over_atlas_rects", GUIAtlas::over);

	/*
	default_atlas_file_name = conf.child("default_atlas").attribute("file").as_string("");
	default_atlas_rects_file_name = conf.child("default_atlas_rects").attribute("file").as_string("");
	over_atlas_file_name = conf.child("over_atlas").attribute("file").as_string("");
	over_atlas_rects_file_name = conf.child("over_atlas_rects").attribute("file").as_string("");
	*/
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	LOG("Loading Gui Atlas");
	for (std::list<Atlas*>::iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
	{
		(item._Ptr->_Myval)->texture = App->tex->Load((item._Ptr->_Myval)->atlas_file_name.c_str());
		(item._Ptr->_Myval)->atlas_content = LoadAtlasRectsXML(&(item._Ptr->_Myval)->atlas_rects_file_name);
	}

	/*
	std::pair<SDL_Texture*, GUIAtlas> new_atlas;

	new_atlas.first = App->tex->Load(default_atlas_file_name.c_str());
	new_atlas.second = GUIAtlas::default;
	atlas_multimap.insert(new_atlas);
	default_atlas_content = LoadAtlasRectsXML(&default_atlas_rects_file_name);

	new_atlas.first = App->tex->Load(over_atlas_file_name.c_str());
	new_atlas.second = GUIAtlas::over;
	atlas_multimap.insert(new_atlas);
	over_atlas_content = LoadAtlasRectsXML(&over_atlas_rects_file_name);
	*/

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Gui::Update(float dt)
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
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
			for (std::list<atlas_element*>::iterator item2 = ((item._Ptr->_Myval)->atlas_content)->begin(); item2 != ((item._Ptr->_Myval)->atlas_content)->cend(); ++item2)
				RELEASE((item2._Ptr->_Myval));
		RELEASE((item._Ptr->_Myval));
	}
	gui_atlas_list.clear();

	/*
	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		App->tex->UnLoad((*item).first);
	atlas_multimap.clear();
	*/

	//TO CLEAN
	/*
	std::list<atlas_element*>* default_atlas_content = nullptr;
	std::list<atlas_element*>* over_atlas_content = nullptr;
	std::list<Gui*> GuiElements;
	std::list<Gui*> ConsoleElements;
	*/
	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas(GUIAtlas atlas) const
{
	for (std::list<Atlas*>::const_iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
		if (item._Ptr->_Myval->atlas_type == atlas)
			return item._Ptr->_Myval->texture;

	/*
	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		if ((*item).second == atlas)
			return (*item).first;
	*/

	return nullptr;
}

void j1Gui::PushBackNewAtlas(pugi::xml_node& conf, char* atlas_file_name, char* atlas_rects_file_name, GUIAtlas AtalsEnum)
{
	gui_atlas_list.push_back(new Atlas(conf.child(atlas_file_name).attribute("file").as_string(""), conf.child(atlas_rects_file_name).attribute("file").as_string(""), AtalsEnum));
}

std::list<atlas_element*>* j1Gui::LoadAtlasRectsXML(std::string* file)
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
			temp->push_back(AllocateNewImageLabelWindow(newimage, atlas_element_type::enum_atlas_image));
		}

		//Iterate all labels stored in XML file
		for (pugi::xml_node newlabel = atlas_config.child("GUI_Label").child("label"); newlabel; newlabel = newlabel.next_sibling("label"))
		{
			temp->push_back(AllocateNewImageLabelWindow(newlabel, atlas_element_type::enum_atlas_label));
		}

		//Iterate all windows stored in XML file
		for (pugi::xml_node newwindow = atlas_config.child("GUI_Window").child("window"); newwindow; newwindow = newwindow.next_sibling("window"))
		{
			temp->push_back(AllocateNewImageLabelWindow(newwindow, atlas_element_type::enum_atlas_window));
		}

		//Iterate all vertical scrollbars stored in XML file
		for (pugi::xml_node newverticalscrollbar = atlas_config.child("GUI_Scrollbar_Vertical").child("scrollbar_vertical"); newverticalscrollbar; newverticalscrollbar = newverticalscrollbar.next_sibling("scrollbar_vertical"))
		{

		}

		//Iterate all horitzontal scrollbars stored in XML file
		for (pugi::xml_node newhoritzontalscrollbar = atlas_config.child("GUI_Scrollbar_Horitzontal").child("scrollbar_horitzontal"); newhoritzontalscrollbar; newhoritzontalscrollbar = newhoritzontalscrollbar.next_sibling("scrollbar_horitzontal"))
		{

		}

		//Iterate all checks stored in XML file
		for (pugi::xml_node newcheck = atlas_config.child("GUI_Check").child("check"); newcheck; newcheck = newcheck.next_sibling("check"))
		{

		}
	}
	return temp;
}

atlas_image_label_window* j1Gui::AllocateNewImageLabelWindow(pugi::xml_node& NewImageLabelWindow, atlas_element_type type)
{
	std::list<SDL_Rect> atlas_element_state_rects;
	for (pugi::xml_node newstate = NewImageLabelWindow.child("state"); newstate; newstate = newstate.next_sibling("state"))
	{
		SDL_Rect newrect = { newstate.attribute("x").as_int(0),newstate.attribute("y").as_int(0),newstate.attribute("w").as_int(0),newstate.attribute("h").as_int(0) };
		atlas_element_state_rects.push_back(newrect);
	}
	atlas_image_label_window* newtoadd = new atlas_image_label_window((char*)NewImageLabelWindow.attribute("name").as_string(""),
		type, NewImageLabelWindow.attribute("animation_loop").as_bool(false), NewImageLabelWindow.attribute("animation_speed").as_float(0.0f),
		&atlas_element_state_rects);
	return newtoadd;
}