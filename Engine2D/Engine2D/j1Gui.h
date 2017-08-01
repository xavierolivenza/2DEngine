#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "Gui.h"

#define CURSOR_WIDTH 2
#define DEBUG_DRAW_ALPHA 80

class MainScene;

enum atlas_element_type;
struct atlas_element;
struct atlas_image_label_window;
struct atlas_button;
struct atlas_check;
struct atlas_scrollbar;

class Gui;
class GuiImage;
class GuiLabel;
class GuiInputText;

enum GUIAtlas
{
	default,
	over,
	fire
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

	const atlas_element* GetAtlasPrefab(atlas_element_type type, std::string* name) const;

	void SetFocus(const Gui* ui);
	const Gui* GetFocus() const;

	bool isDebugDrawActive() const;

	GuiImage* CreateImage(char* elementname, iPoint position, j1Module* module_listener, bool movable = false, bool can_focus = false,
		bool move_with_camera = true, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiImage* CreateImage(char* elementname, iPoint position, MainScene* scene_listener, bool movable = false, bool can_focus = false,
		bool move_with_camera = true, AddGuiTo addto = AddGuiTo::regular_purpose);

	GuiLabel* CreateLabel(char* str, char* elementname, iPoint position, j1Module* module_listener, bool movable = false,
		bool can_focus = false, bool move_with_camera = true, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiLabel* CreateLabel(char* str, char* elementname, iPoint position, MainScene* scene_listener, bool movable = false,
		bool can_focus = false, bool move_with_camera = true, AddGuiTo addto = AddGuiTo::regular_purpose);

	GuiInputText* CreateGuiInputText(char* str, char* elementname, iPoint position, j1Module* module_listener, bool isPassword = false,
		bool movable = false, bool can_focus = false, bool move_with_camera = true, AddGuiTo addto = AddGuiTo::regular_purpose);
	GuiInputText* CreateGuiInputText(char* str, char* elementname, iPoint position, MainScene* scene_listener, bool isPassword = false,
		bool movable = false, bool can_focus = false, bool move_with_camera = true, AddGuiTo addto = AddGuiTo::regular_purpose);

private:
	void PushBackNewAtlas(pugi::xml_node& conf, GUIAtlas AtalsEnum);
	std::list<atlas_element*>* LoadAtlasRectsXML(std::string* file, SDL_Texture* atlas_texture);
	atlas_image_label_window* AllocateNewImageLabelWindow(pugi::xml_node& NewImageLabelWindow, atlas_element_type type, SDL_Texture* atlas_texture);
	atlas_button* AllocateNewButton(pugi::xml_node& NewButton, SDL_Texture* atlas_texture);
	atlas_check* AllocateNewCheck(pugi::xml_node& NewCheck, SDL_Texture* atlas_texture);
	atlas_scrollbar* AllocateNewScrollbar(pugi::xml_node& NewCheck, atlas_element_type type, SDL_Texture* atlas_texture);

	const Gui* FindMouseHover();
	bool CanInteract(const Gui* ui) const;

	void push_back_gui(Gui* gui, AddGuiTo addto);

private:
	bool Gui_DebugDraw = false;

	//All atlas stored
	std::list<Atlas*> gui_atlas_list;

	//Gui/Console Elements Lists
	std::list<Gui*> GuiElements;
	std::list<Gui*> ConsoleElements;

	Gui* focus = nullptr;

	iPoint cameraPos = { 0,0 };
};

#endif // __j1GUI_H__