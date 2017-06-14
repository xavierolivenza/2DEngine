#ifndef _MAINSCENE_
#define _MAINSCENE_

#include "SDL\include\SDL.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "p2Log.h"

class MainScene {
public:

	MainScene() {}

	~MainScene() {}

	virtual bool Awake(pugi::xml_node& conf)
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool PreUpdate()
	{
		return true;
	}

	virtual bool Update()
	{
		return true;
	}

	virtual bool PostUpdate()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual void OnGui(Gui* ui, GuiEvent event)
	{

	}

public:
	std::string scene_name;

};

#endif // _MAINSCENE_