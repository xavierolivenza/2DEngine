#ifndef _TEST_SCENE_3_
#define _TEST_SCENE_3_

#include "MainScene.h"

class S_TestScene_3 : public MainScene {

public:
	S_TestScene_3();
	~S_TestScene_3();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:

};

#endif // 