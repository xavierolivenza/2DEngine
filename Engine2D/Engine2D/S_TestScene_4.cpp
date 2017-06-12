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