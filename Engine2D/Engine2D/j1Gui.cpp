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

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	std::pair<SDL_Texture*, GUIAtlas> new_atlas;

	new_atlas.first = App->tex->Load(atlas_file_name.c_str());
	new_atlas.second = GUIAtlas::default;
	atlas_multimap.insert(new_atlas);

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

	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		App->tex->UnLoad((*item).first);
	atlas_multimap.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas(GUIAtlas atlas) const
{
	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		if ((*item).second == atlas)
			return (*item).first;

	return nullptr;
}