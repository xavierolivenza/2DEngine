#include "S_TestScene_1.h"

S_TestScene_1::S_TestScene_1()
{
	scene_name = "S_TestScene_1";
}

S_TestScene_1::~S_TestScene_1()
{

}

bool S_TestScene_1::Awake(pugi::xml_node& conf)
{
	return true;
}

void  S_TestScene_1::CreateSceneGUI()
{
	testimage1 = App->gui->CreateImage("default_image", { 0,0 }, this, false, false, true, AddGuiTo::regular_purpose);
	testimage2 = App->gui->CreateImage("pixel_fire", { 200,200 }, this, true, false, false, AddGuiTo::regular_purpose);
	testlabel1 = App->gui->CreateLabel("hello world 1", "default_label", { 500,50 }, this, false, false, true, AddGuiTo::regular_purpose);
	testlabel2 = App->gui->CreateLabel("hello world 2", "default_label", { 500,200 }, this, true, false, false, AddGuiTo::regular_purpose);
}

bool S_TestScene_1::Start()
{
	if (App->map->Load("scene_1.tmx") == true)
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

bool S_TestScene_1::PreUpdate()
{
	return true;
}

bool S_TestScene_1::Update()
{
	return true;
}

bool S_TestScene_1::PostUpdate()
{
	return true;
}

bool S_TestScene_1::CleanUp()
{
	return true;
}