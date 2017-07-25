#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"

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
	for (std::list<Atlas*>::iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
	{
		(*item)->texture = App->tex->Load((*item)->atlas_file_name.c_str());
		(*item)->atlas_content = LoadAtlasRectsXML(&(*item)->atlas_rects_file_name);
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
	/*
	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		if ((*item).second == atlas)
			return (*item).first;
	*/



	return nullptr;
}

void j1Gui::PushBackNewAtlas(pugi::xml_node& conf, char* atlas_file_name, char* atlas_rects_file_name, GUIAtlas AtalsEnum)
{
	gui_atlas_list.push_back(new Atlas(conf.child("atlas_file_name").attribute("file").as_string(""), conf.child("atlas_rects_file_name").attribute("file").as_string(""), AtalsEnum));
}

std::list<atlas_element*>* j1Gui::LoadAtlasRectsXML(std::string* file)
{
	std::list<atlas_element*>* temp = new std::list<atlas_element*>;







	return temp;
}