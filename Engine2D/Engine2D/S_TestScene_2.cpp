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