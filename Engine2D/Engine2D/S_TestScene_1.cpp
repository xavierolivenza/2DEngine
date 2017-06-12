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