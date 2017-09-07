#include "S_TestScene_3.h"

S_TestScene_3::S_TestScene_3()
{
	scene_name = "S_TestScene_3";
}

S_TestScene_3::~S_TestScene_3()
{

}

bool S_TestScene_3::Awake(pugi::xml_node& conf)
{
	return true;
}

void S_TestScene_3::CreateSceneGUI()
{
	testwindow1 = App->gui->CreateGuiWindow("default_window", { 0,0 }, this, false, false, true, AddGuiTo::regular_purpose);
	testwindow2 = App->gui->CreateGuiWindow("default_window", { 500,0 }, this, true, false, false, AddGuiTo::regular_purpose);
}

bool S_TestScene_3::Start()
{
	if (App->map->Load("scene_3.tmx") == true)
	{
		int w = 0;
		int h = 0;
		uchar* data = nullptr;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
	}
	return true;
}

bool S_TestScene_3::PreUpdate()
{
	return true;
}

bool S_TestScene_3::Update()
{
	return true;
}

bool S_TestScene_3::PostUpdate()
{
	return true;
}

bool S_TestScene_3::CleanUp()
{
	return true;
}