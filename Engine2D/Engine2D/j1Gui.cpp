#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1FileSystem.h"

j1Gui::j1Gui() : j1Module()
{
	name = "gui";
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	PushBackNewAtlas(conf, "default_atlas", "default_atlas_rects", GUIAtlas::default);
	PushBackNewAtlas(conf, "over_atlas", "over_atlas_rects", GUIAtlas::over);

	/*
	default_atlas_file_name = conf.child("default_atlas").attribute("file").as_string("");
	default_atlas_rects_file_name = conf.child("default_atlas_rects").attribute("file").as_string("");
	over_atlas_file_name = conf.child("over_atlas").attribute("file").as_string("");
	over_atlas_rects_file_name = conf.child("over_atlas_rects").attribute("file").as_string("");
	*/
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	LOG("Loading Gui Atlas");
	for (std::list<Atlas*>::iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
	{
		(*item)->texture = App->tex->Load((*item)->atlas_file_name.c_str());
		(*item)->atlas_content = LoadAtlasRectsXML(&(*item)->atlas_rects_file_name);
	}

	/*
	std::pair<SDL_Texture*, GUIAtlas> new_atlas;

	new_atlas.first = App->tex->Load(default_atlas_file_name.c_str());
	new_atlas.second = GUIAtlas::default;
	atlas_multimap.insert(new_atlas);
	default_atlas_content = LoadAtlasRectsXML(&default_atlas_rects_file_name);

	new_atlas.first = App->tex->Load(over_atlas_file_name.c_str());
	new_atlas.second = GUIAtlas::over;
	atlas_multimap.insert(new_atlas);
	over_atlas_content = LoadAtlasRectsXML(&over_atlas_rects_file_name);
	*/

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Gui::Update(float dt)
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (std::list<Atlas*>::iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
	{
		if ((item._Ptr->_Myval)->texture != nullptr)
			App->tex->UnLoad((item._Ptr->_Myval)->texture);
		if ((item._Ptr->_Myval)->atlas_content != nullptr)
			for (std::list<atlas_element*>::iterator item2 = ((item._Ptr->_Myval)->atlas_content)->begin(); item2 != ((item._Ptr->_Myval)->atlas_content)->cend(); ++item2)
				RELEASE((item2._Ptr->_Myval));
		RELEASE((item._Ptr->_Myval));
	}
	gui_atlas_list.clear();

	/*
	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		App->tex->UnLoad((*item).first);
	atlas_multimap.clear();
	*/

	//TO CLEAN
	/*
	std::list<atlas_element*>* default_atlas_content = nullptr;
	std::list<atlas_element*>* over_atlas_content = nullptr;
	std::list<Gui*> GuiElements;
	std::list<Gui*> ConsoleElements;
	*/
	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas(GUIAtlas atlas) const
{
	for (std::list<Atlas*>::const_iterator item = gui_atlas_list.begin(); item != gui_atlas_list.cend(); ++item)
		if (item._Ptr->_Myval->atlas_type == atlas)
			return item._Ptr->_Myval->texture;

	/*
	for (std::multimap<SDL_Texture*, GUIAtlas>::const_iterator item = atlas_multimap.begin(); item != atlas_multimap.cend(); ++item)
		if ((*item).second == atlas)
			return (*item).first;
	*/

	return nullptr;
}

void j1Gui::PushBackNewAtlas(pugi::xml_node& conf, char* atlas_file_name, char* atlas_rects_file_name, GUIAtlas AtalsEnum)
{
	gui_atlas_list.push_back(new Atlas(conf.child("atlas_file_name").attribute("file").as_string(""), conf.child("atlas_rects_file_name").attribute("file").as_string(""), AtalsEnum));
}

std::list<atlas_element*>* j1Gui::LoadAtlasRectsXML(std::string* file)
{
	std::list<atlas_element*>* temp = nullptr;

	LOG("Loading XML file %s", file->c_str());

	pugi::xml_document	config_file;
	pugi::xml_node		atlas_config;

	char* buffer = nullptr;
	int size = App->fs->Load(file->c_str(), &buffer);
	pugi::xml_parse_result result = config_file.load_buffer(buffer, size);
	RELEASE(buffer);

	if (result == NULL)
		LOG("Could not load XML file %s. pugi error: %s", file->c_str(), result.description());
	else
		atlas_config = config_file.child("gui_atlas_rects");

	if (!atlas_config.empty())
	{
		temp = new std::list<atlas_element*>;

		//Iterate all images stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Image").child("image"); newimage; newimage = newimage.next_sibling("image"))
		{
			
		}

		//Iterate all labels stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Label").child("label"); newimage; newimage = newimage.next_sibling("label"))
		{

		}

		//Iterate all windows stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Window").child("window"); newimage; newimage = newimage.next_sibling("window"))
		{

		}

		//Iterate all vertical scrollbars stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Scrollbar_Vertical").child("scrollbar_vertical"); newimage; newimage = newimage.next_sibling("scrollbar_vertical"))
		{

		}

		//Iterate all horitzontal scrollbars stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Scrollbar_Horitzontal").child("scrollbar_horitzontal"); newimage; newimage = newimage.next_sibling("scrollbar_horitzontal"))
		{

		}

		//Iterate all checks stored in XML file
		for (pugi::xml_node newimage = atlas_config.child("GUI_Check").child("check"); newimage; newimage = newimage.next_sibling("check"))
		{

		}

	}




	/*
	for (pugi::xml_node newcharacterrect = dialoguenode.child("Rects").child("rect"); newcharacterrect; newcharacterrect = newcharacterrect.next_sibling("rect"), sprite_id++)
	{
		CharaterSprite* newCharaterSprite = new CharaterSprite();
		newCharaterSprite->sprite_id = (CharaterSpriteRect_ID)sprite_id;
		newCharaterSprite->CharaterSpriteRect = { newcharacterrect.attribute("x").as_int(0) ,newcharacterrect.attribute("y").as_int(0) ,newcharacterrect.attribute("w").as_int(0) ,newcharacterrect.attribute("h").as_int(0) };
		CharaterSpritesVec.push_back(newCharaterSprite);
	}
	*/

	/*
	dialogues.push_back(new Dialogue());
	Dialogue* newdialogue = dialogues.back();
	newdialogue->id = (DialogueID)dialoguenode.attribute("enum_value").as_int();
	newdialogue->type = type;
	for (pugi::xml_node newstep = dialoguenode.child("step"); newstep; newstep = newstep.next_sibling("step"))
	{
		newdialogue->DialogueSteps.push_back(new DialogueStep());
		DialogueStep* newdialoguestep = newdialogue->DialogueSteps.back();
		newdialoguestep->SpeakerDialogueCharacter = new DialogueCharacter();
		newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newstep.attribute("speaker").as_string()));
		if (newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id == DialogueInterlucutor::item_nullinterlucutor)
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string("");
		else
			newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_str = std::string(newstep.attribute("speaker").as_string());
		newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newstep.attribute("speaker_pos").as_string()));
		newdialoguestep->SpeakerDialogueCharacter->Character_Atlas = CheckInterlocutorAtlas(newdialoguestep->SpeakerDialogueCharacter->DialogueCharacter_id);
		newdialoguestep->SpeakerDialogueCharacter->Character_Expression_Rect = CheckExpressionRect((CharaterSpriteRect_ID)newstep.attribute("speaker_expression").as_int(0));
		newdialoguestep->ListenerDialogueCharacter = new DialogueCharacter();
		newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id = CheckInterlocutor(&std::string(newstep.attribute("listener").as_string()));
		if (newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id == DialogueInterlucutor::item_nullinterlucutor)
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string("");
		else
			newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_str = std::string(newstep.attribute("listener").as_string());
		newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_pos = CheckInterlocutorPosition(&std::string(newstep.attribute("listener_pos").as_string()));
		newdialoguestep->ListenerDialogueCharacter->Character_Atlas = CheckInterlocutorAtlas(newdialoguestep->ListenerDialogueCharacter->DialogueCharacter_id);
		newdialoguestep->ListenerDialogueCharacter->Character_Expression_Rect = CheckExpressionRect((CharaterSpriteRect_ID)newstep.attribute("listener_expression").as_int(0));
		int y = 0;
		for (pugi::xml_node newsteplines = newstep.child("line"); newsteplines; newsteplines = newsteplines.next_sibling("line"), y += 30)
		{
			newdialoguestep->lines.push_back(App->gui->CreateLabel({ TextBackgroundPos->x + 60,TextBackgroundPos->y + 60 + y }, &std::string(newsteplines.child_value()), false, AddGuiTo::none));
			newdialoguestep->lines.back()->SetFont(App->font->ReturnofGanon36);
		}
	}
	*/

	return temp;
}