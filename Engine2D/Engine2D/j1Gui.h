#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"

#define CURSOR_WIDTH 2

enum GUIAtlas
{
	default,
	over
};

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	SDL_Texture* GetAtlas(GUIAtlas atlas) const;

private:


private:

	std::multimap<SDL_Texture*, GUIAtlas> atlas_multimap;
	std::string default_atlas_file_name;
	std::string over_atlas_file_name;
};

#endif // __j1GUI_H__