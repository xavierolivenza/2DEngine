#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1FileSystem.h"
#include "j1Scene.h"

#include "S_TestScene_1.h"
#include "S_TestScene_2.h"
#include "S_TestScene_3.h"
#include "S_TestScene_4.h"
#include "S_TestScene_5.h"

j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	bool ret = false;
	MainScene* new_scene = nullptr;

	new_scene = new S_TestScene_1;
	scene_list.push_back(new_scene);
	active_scene = new_scene;

	new_scene = new S_TestScene_2;
	scene_list.push_back(new_scene);

	new_scene = new S_TestScene_3;
	scene_list.push_back(new_scene);

	new_scene = new S_TestScene_4;
	scene_list.push_back(new_scene);

	new_scene = new S_TestScene_5;
	scene_list.push_back(new_scene);

	//XML congig read
	pugi::xml_document	config_file;
	pugi::xml_node		config;

	//Load XML
	char* buf = nullptr;
	int size = App->fs->Load("scenes/scenes_config.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load map xml file gui_config.xml. pugi error: %s", result.description());
	else
		config = config_file.child("scenes_config");

	//Set config
	if (config.empty() == false)
		ret = true;

	if (ret == true)
		for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend() && ret == true; ++item)
			ret = (item._Ptr->_Myval)->Awake(config.child((item._Ptr->_Myval)->scene_name.c_str()));

	debug_tex = App->tex->Load("maps/path2.png");

	return ret;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	if (active_scene != prev_active_scene)
	{
		active_scene->Start();
		prev_active_scene = active_scene;
	}
	active_scene->PreUpdate();

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x = 0;
	int y = 0;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	active_scene->Update();

	//---------------------------------------------------------------------------------------------------------//
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		ChangeScene(std::string("S_TestScene_1"));
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		ChangeScene(std::string("S_TestScene_2"));
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		ChangeScene(std::string("S_TestScene_3"));
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		ChangeScene(std::string("S_TestScene_4"));
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		ChangeScene(std::string("S_TestScene_5"));
	//---------------------------------------------------------------------------------------------------------//

	// -------
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 1;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 1;
	/*
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);
	*/
	App->map->Draw();

	int x = 0;
	int y = 0;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	
	// Debug pathfinding ------------------------------
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const std::vector<iPoint>* path = App->pathfinding->GetLastPath();

	for (std::vector<iPoint>::const_iterator item = path->begin(); item != path->cend(); ++item)
	{
		iPoint pos = App->map->MapToWorld(item._Ptr->x, item._Ptr->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	active_scene->PostUpdate();

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	active_scene->CleanUp();

	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
		RELEASE(item._Ptr->_Myval);

	return true;
}

bool j1Scene::ChangeScene(std::string& scene_name)
{
	for (std::list<MainScene*>::iterator item = scene_list.begin(); item != scene_list.cend(); ++item)
		if ((item._Ptr->_Myval)->scene_name == scene_name)
		{
			if (item._Ptr->_Myval != active_scene)
				active_scene->CleanUp();
			active_scene = item._Ptr->_Myval;
			return true;
		}
	return false;
}

const MainScene* j1Scene::GetActiveScene() const
{
	return active_scene;
}