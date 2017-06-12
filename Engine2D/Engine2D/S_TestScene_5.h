#ifndef _TEST_SCENE_5_
#define _TEST_SCENE_5_

#include "MainScene.h"

class S_TestScene_5 : public MainScene {

public:
	S_TestScene_5();
	~S_TestScene_5();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:

};

#endif // 