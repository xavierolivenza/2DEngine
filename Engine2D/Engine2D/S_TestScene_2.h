#ifndef _TEST_SCENE_2_
#define _TEST_SCENE_2_

#include "MainScene.h"

class S_TestScene_2 : public MainScene {

public:
	S_TestScene_2();
	~S_TestScene_2();
	bool Awake(pugi::xml_node& conf);
	void CreateSceneGUI();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:
	GuiButton* testbutton1 = nullptr;
	GuiButton* testbutton2 = nullptr;
	GuiCheck* testcheck1 = nullptr;
	GuiCheck* testcheck2 = nullptr;
	GuiCheck* testcheck3 = nullptr;
	GuiCheck* testcheck4 = nullptr;
};

#endif // 