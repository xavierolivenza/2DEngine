#ifndef __GUI_H__
#define __GUI_H__

#include "p2Log.h"
#include "j1Module.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Color.h"

enum GuiType
{
	gui_image,
	gui_button,
	gui_check,
	gui_inputtext,
	gui_label,
	gui_bar,
	gui_scrollbar,
	gui_window,
	gui_viewport,
	null_GuiType
};

enum GuiEvent
{
	mouse_enter,
	mouse_leave,
	mouse_lclk_down,
	mouse_lclk_repeat,
	mouse_lclk_up,
	mouse_rclk_down,
	mouse_rclk_repeat,
	mouse_rclk_up,
	gain_focus,
	lost_focus,

	/*
	listening_ends,
	input_changed,
	input_submit,
	value_changed
	*/

	null_GuiEvent
};

enum AddGuiTo
{
	regular_purpose,
	console_purpose,
	viewport_purpose,
	null_AddGuiTo
};

enum ButtonType
{
	idle_only,
	idle_hover,
	idle_pressed,
	idle_hover_pressed,
	null_ButtonType
};

enum BarType
{
	vertical_up,
	vertical_down,
	horitzontal_left,
	horitzontal_right,
	null_BarType
};

class MainScene;

class Gui
{
	//friend class j1Gui;
public:
	Gui(iPoint position, GuiType type, bool movable, AddGuiTo purpose);
	virtual ~Gui() {}
	virtual void Update(const Gui* mouse_hover, const Gui* focus) {}
	virtual void Draw() {}
	virtual void DebugDraw() const {}

	void SetLocalPos(int x, int y);
	iPoint GetLocalPos() const;
	void GetLocalPos(int& x, int& y) const;
	void Move(int x, int y);
	void SetDragVelocity(float x, float y);
	fPoint GetDragVelocity() const;
	void GetDragVelocity(float& x, float& y) const;
	bool IsMovable() const;

	void SetVisible(bool visible);
	void SetOpacity(int alpha);
	int GetOpacity() const;
	void GainOpacityOverTime(int initialalpha, int finalalpha, int transitionmilisec);
	void GainOpacityOverTime(int finalalpha, int transitionmilisec); //Starts at actual alpha
	void LossOpacityOverTime(int initialalpha, int finalalpha, int transitionmilisec);
	void LossOpacityOverTime(int finalalpha, int transitionmilisec); //Starts at actual alpha

	void SetFocus(bool value);
	Gui* GetFocus() const;
	bool Focusable() const;
	
	AddGuiTo GetPurpose() const;
	bool InFOV();
	bool PointContained(int x, int y) const;
	void CheckInput(const Gui* mouse_hover, const Gui* focus);
	
	void SetListener(j1Module* module);
	void SetListener(MainScene* module);
	const j1Module* GetModuleListener() const;
	const MainScene* GetSceneListener() const;

protected:
	AddGuiTo purpose;
	GuiType type = GuiType::null_GuiType;
	iPoint position = { 0,0 };
	fPoint drag_vel = { 0.0f, 0.0f };
	bool visible = true;
	bool movable = false;
	uint opacity = 255; //0-255
	bool can_focus = false;
	SDL_Rect Gui_Collider = { 0,0,0,0 };
	
	bool mouse_inside = false;
	j1Module* module_listener = nullptr;
	MainScene* scene_listener = nullptr;
};

#endif // __GUI_H__