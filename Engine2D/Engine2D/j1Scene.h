#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "MainScene.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool ChangeScene(std::string& scene_name);

	const MainScene* GetActiveScene() const;

private:
	bool TimeToCreateGUI = true;

	MainScene* active_scene = nullptr;
	MainScene* prev_active_scene = nullptr;
	std::list<MainScene*> scene_list;

	SDL_Texture* debug_tex = nullptr;

};

#endif // __j1SCENE_H__