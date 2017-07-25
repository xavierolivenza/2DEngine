#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "Gui.h"
#include "GuiXMLStorage.h"

#define CURSOR_WIDTH 2

enum GUIAtlas
{
	default,
	over
};

struct Atlas
{
	Atlas(std::string file_name, std::string rects_file_name, GUIAtlas enum_value) : atlas_file_name(file_name), atlas_rects_file_name(rects_file_name), atlas_type(enum_value)
	{

	}
	GUIAtlas atlas_type = GUIAtlas::default;
	std::string atlas_file_name;
	std::string atlas_rects_file_name;
	SDL_Texture* texture = nullptr;
	std::list<atlas_element*>* atlas_content = nullptr;
};

// ---------------------------------------------------
class j1Gui : public j1Module
{
	friend class Gui;
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
	void PushBackNewAtlas(pugi::xml_node& conf, char* atlas_file_name, char* atlas_rects_file_name, GUIAtlas AtalsEnum);
	std::list<atlas_element*>* LoadAtlasRectsXML(std::string* file);

private:
	bool Gui_DebugDraw = false;

	//All atlas stored
	std::list<Atlas*> gui_atlas_list;

	/*
	//All atlas stored
	std::multimap<SDL_Texture*, GUIAtlas> atlas_multimap;

	//Default Atlas
	std::string default_atlas_file_name;
	std::string default_atlas_rects_file_name;
	std::list<atlas_element*>* default_atlas_content = nullptr;

	//Over Atlas
	std::string over_atlas_file_name;
	std::string over_atlas_rects_file_name;
	std::list<atlas_element*>* over_atlas_content = nullptr;
	*/

	//Gui/Console Elements Lists
	std::list<Gui*> GuiElements;
	std::list<Gui*> ConsoleElements;

	Gui* focus = nullptr;
};

#endif // __j1GUI_H__