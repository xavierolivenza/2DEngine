#ifndef _TEST_SCENE_4_
#define _TEST_SCENE_4_

#include "MainScene.h"

class S_TestScene_4 : public MainScene {

public:
	S_TestScene_4();
	~S_TestScene_4();
	bool Awake(pugi::xml_node& conf);
	void CreateSceneGUI();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:
	GuiViewport* testviewport1 = nullptr;
	GuiViewport* testviewport2 = nullptr;

};

#endif // 