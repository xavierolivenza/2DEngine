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
	testbutton1 = App->gui->CreateButton("static button", ButtonType::idle_hover_pressed, "default_button_big", { 0,0 }, this, false, false, true, AddGuiTo::regular_purpose);
	testbutton2 = App->gui->CreateButton("movable button", ButtonType::idle_hover_pressed, "default_button_big", { 300,0 }, this, true, false, false, AddGuiTo::regular_purpose);
	testcheck1 = App->gui->CreateCheck("default_check_three_tex", false, { 0,300 }, this, false, false, true, AddGuiTo::regular_purpose);
	testcheck2 = App->gui->CreateCheck("default_check_three_tex", false, { 100,300 }, this, true, false, false, AddGuiTo::regular_purpose);
	testcheck3 = App->gui->CreateCheck("default_check_two_tex", false, { 200,300 }, this, false, false, true, AddGuiTo::regular_purpose);
	testcheck4 = App->gui->CreateCheck("default_check_two_tex", false, { 300,300 }, this, true, false, false, AddGuiTo::regular_purpose);
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