#ifndef __j1APP_H__
#define __j1APP_H__

#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1FileSystem;
class j1Scene;
class j1Map;
class j1PathFinding;
class j1Fonts;
class j1Gui;
class j1Console;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(std::list<std::string>& list_to_fill) const;

	void WantToQuit();

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	// Modules
	j1Window*			win = nullptr;
	j1Input*			input = nullptr;
	j1Render*			render = nullptr;
	j1Textures*			tex = nullptr;
	j1Audio*			audio = nullptr;
	j1Scene*			scene = nullptr;
	j1FileSystem*		fs = nullptr;
	j1Map*				map = nullptr;
	j1PathFinding*		pathfinding = nullptr;
	j1Fonts*			font = nullptr;
	j1Gui*				gui = nullptr;
	j1Console*			console = nullptr;

private:

	std::list<j1Module*>	modules;
	int					argc = 0;
	char**				args = nullptr;

	std::string			title;
	std::string			organization;

	mutable bool		want_to_save = false;
	bool				want_to_load = false;
	std::string			load_game;
	mutable std::string	save_game;

	j1PerfTimer			ptimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;

	bool				wanttoquit = false;
};

extern j1App* App;

#endif