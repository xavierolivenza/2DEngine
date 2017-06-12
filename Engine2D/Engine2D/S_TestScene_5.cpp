#include "S_TestScene_5.h"

S_TestScene_5::S_TestScene_5()
{
	scene_name = "S_TestScene_5";
}

S_TestScene_5::~S_TestScene_5()
{

}

bool S_TestScene_5::Awake(pugi::xml_node& conf)
{
	return true;
}

bool S_TestScene_5::Start()
{
	if (App->map->Load("scene_5.tmx") == true)
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

bool S_TestScene_5::PreUpdate()
{
	return true;
}

bool S_TestScene_5::Update()
{
	return true;
}

bool S_TestScene_5::PostUpdate()
{
	return true;
}

bool S_TestScene_5::CleanUp()
{
	return true;
}