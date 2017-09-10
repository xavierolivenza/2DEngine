#include "S_TestScene_4.h"

S_TestScene_4::S_TestScene_4()
{
	scene_name = "S_TestScene_4";
}

S_TestScene_4::~S_TestScene_4()
{

}

bool S_TestScene_4::Awake(pugi::xml_node& conf)
{
	return true;
}

void S_TestScene_4::CreateSceneGUI()
{
	SDL_Rect viewport = { 0,0,400,400 };
	testviewport1 = App->gui->CreateViewport(&viewport, this, false, false, true, AddGuiTo::regular_purpose);
	testviewport1->push_back_item(App->gui->CreateImage("pixel_fire", { 0,0 }, this, true, false, false, AddGuiTo::viewport_purpose));
	testviewport1->push_back_item(App->gui->CreateLabel("hello world 1", "default_label", { 100,50 }, this, false, false, true, AddGuiTo::viewport_purpose));
	testviewport1->push_back_item(App->gui->CreateLabel("hello world 2", "", { 50,200 }, this, true, true, true, AddGuiTo::viewport_purpose));
	testviewport1->push_back_item(App->gui->CreateGuiInputText("input text", "default_label", { 200,200 }, this, false, true, true, true, AddGuiTo::viewport_purpose));
	viewport = { 500,0,400,400 };
	testviewport2 = App->gui->CreateViewport(&viewport, this, true, false, false, AddGuiTo::regular_purpose);
	testviewport2->push_back_item(App->gui->CreateImage("pixel_fire", { 0,0 }, this, true, false, false, AddGuiTo::viewport_purpose));
	testviewport2->push_back_item(App->gui->CreateLabel("hello world 1", "default_label", { 100,50 }, this, false, false, true, AddGuiTo::viewport_purpose));
	testviewport2->push_back_item(App->gui->CreateLabel("hello world 2", "", { 50,200 }, this, true, true, true, AddGuiTo::viewport_purpose));
	testviewport2->push_back_item(App->gui->CreateGuiInputText("input text", "default_label", { 200,200 }, this, false, true, true, true, AddGuiTo::viewport_purpose));
}

bool S_TestScene_4::Start()
{
	if (App->map->Load("scene_4.tmx") == true)
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

bool S_TestScene_4::PreUpdate()
{
	return true;
}

bool S_TestScene_4::Update()
{
	return true;
}

bool S_TestScene_4::PostUpdate()
{
	return true;
}

bool S_TestScene_4::CleanUp()
{
	return true;
}