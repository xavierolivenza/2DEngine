#include "S_TestScene_1.h"
#include "j1Input.h"

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
	testlabel2 = App->gui->CreateLabel("hello world 2", "", { 500,200 }, this, true, true, true, AddGuiTo::regular_purpose);
	inputtexttest1 = App->gui->CreateGuiInputText("input text", "default_label", { 500,500 }, this, false, true, true, true, AddGuiTo::regular_purpose);
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
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		testimage1->SetAnimationFrameMiliseconds(10);
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		testimage1->SetAnimationFrameMiliseconds(200);
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{

	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		testlabel1->ChangeStr(&std::string("change 2"));
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		testlabel1->SetStrOffset(100,-50);
	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN)
		testlabel1->CenterStrWithBackground();
	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
		testlabel1->SetStrColor(255,100,50);
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		testlabel1->SetStrColor(0,0,0);
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{

	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{

	}
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