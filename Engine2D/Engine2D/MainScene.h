#ifndef _MAINSCENE_
#define _MAINSCENE_

#include "j1App.h"
#include "SDL\include\SDL.h"
#include "p2Log.h"

class MainScene {
public:

	MainScene() {};
	~MainScene() {};

	virtual bool Awake(pugi::xml_node& conf) {
		return true;
	};
	virtual bool Start() {
		return true;
	};
	virtual bool PreUpdate() {
		return true;
	};
	virtual bool Update() {
		return true;
	};
	virtual bool PostUpdate() {
		return true;
	};
	virtual bool CleanUp() {
		return true;
	}

public:
	std::string scene_name;

};

#endif // _MAINSCENE_