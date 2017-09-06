#include "S_TestScene_2.h"

S_TestScene_2::S_TestScene_2()
{
	scene_name = "S_TestScene_2";
}

S_TestScene_2::~S_TestScene_2()
{

}

bool S_TestScene_2::Awake(pugi::xml_node& conf)
{
	return true;
}

void  S_TestScene_2::CreateSceneGUI()
{
	testbutton1 = App->gui->CreateButton("fdsfa", ButtonType::idle_hover_pressed, "default_button_big", { 0,0 }, this, false, false, true, AddGuiTo::regular_purpose);
	testbutton2 = App->gui->CreateButton("gfdsgdfg", ButtonType::idle_hover_pressed, "default_button_big", { 200,0 }, this, true, false, false, AddGuiTo::regular_purpose);
}

bool S_TestScene_2::Start()
{
	if (App->map->Load("scene_2.tmx") == true)
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

bool S_TestScene_2::PreUpdate()
{
	return true;
}

bool S_TestScene_2::Update()
{
	return true;
}

bool S_TestScene_2::PostUpdate()
{
	return true;
}

bool S_TestScene_2::CleanUp()
{
	return true;
}