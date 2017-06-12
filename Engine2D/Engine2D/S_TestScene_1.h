#ifndef _ENDSCENE_
#define _ENDSCENE_

#include "MainScene.h"

class S_TestScene_1 : public MainScene {

public:
	S_TestScene_1();
	~S_TestScene_1();
	bool Awake(pugi::xml_node& conf);
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

public:

};

#endif // 