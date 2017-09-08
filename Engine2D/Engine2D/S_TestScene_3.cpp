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
	testwindow1->push_back_item(App->gui->CreateImage("pixel_fire", { 0,0 }, this, true, false, false, AddGuiTo::window_purpose));
	testwindow1->push_back_item(App->gui->CreateLabel("hello world 1", "default_label", { 100,50 }, this, false, false, true, AddGuiTo::window_purpose));
	testwindow1->push_back_item(App->gui->CreateLabel("hello world 2", "", { 50,200 }, this, true, true, true, AddGuiTo::window_purpose));
	testwindow1->push_back_item(App->gui->CreateGuiInputText("input text", "default_label", { 200,200 }, this, false, true, true, true, AddGuiTo::window_purpose));

	testwindow2 = App->gui->CreateGuiWindow("default_window", { 500,0 }, this, true, false, false, AddGuiTo::regular_purpose);
	testwindow2->push_back_item(App->gui->CreateImage("pixel_fire", { 500,0 }, this, true, false, false, AddGuiTo::window_purpose));
	testwindow2->push_back_item(App->gui->CreateLabel("hello world 1", "default_label", { 600,50 }, this, false, false, true, AddGuiTo::window_purpose));
	testwindow2->push_back_item(App->gui->CreateLabel("hello world 2", "", { 550,200 }, this, true, true, true, AddGuiTo::window_purpose));
	testwindow2->push_back_item(App->gui->CreateGuiInputText("input text", "default_label", { 700,200 }, this, false, true, true, true, AddGuiTo::window_purpose));
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
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		testwindow1->SetVisible(true);
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		testwindow1->SetVisible(false);
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		testwindow2->SetVisible(true);
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		testwindow2->SetVisible(false);
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