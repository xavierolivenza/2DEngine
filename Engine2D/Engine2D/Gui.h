#ifndef __GUI_H__
#define __GUI_H__

#include "j1App.h"
#include "j1Module.h"
#include "Color.h"
#include "Animation.h"
#include "GuiXMLStorage.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Fonts.h"

static Color GuiImageDebugColor = Red;
static Color GuiLabelDebugColor = Green;
static Color GuiInputTextDebugColor = Blue;
static Color GuiWindowDebugColor = Yellow;
static Color GuiButtonDebugColor = Purple;
static Color GuiScrollBarDebugColor = White;
static Color GuiCheckDebugColor = Cyan;
static Color GuiViewportDebugColor = Pink;

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
	window_purpose,
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

enum ScrollBarType
{
	vertical_left,
	vertical_right,
	horitzontal_up,
	horitzontal_down,
	null_ScrollBarType
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
class GuiWindow;
class GuiViewport;

class Gui
{
	friend class j1Gui;
public:
	Gui(iPoint position, GuiType type, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo purpose);
	Gui(iPoint position, GuiType type, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo purpose);
	virtual ~Gui() {}
	virtual void Update(const Gui* mouse_hover, const Gui* focus) {}
	virtual void Draw() {}
	virtual void DebugDraw() const {}
	virtual void FocusGained() {}
	virtual void FocusLost() {}

	void SetLocalPos(int x, int y);
	iPoint GetLocalPos() const;
	void GetLocalPos(int& x, int& y) const;
	void Move(int x, int y);
	void SetDragVelocity(float x, float y);
	fPoint GetDragVelocity() const;
	void GetDragVelocity(float& x, float& y) const;
	bool IsMovable() const;

	void SetCollider(int x, int y, int w, int h);
	void SetCollider(SDL_Rect* collider);

	void SetVisible(bool visible);
	void SetOpacity(uint alpha);
	int GetOpacity() const;
	void GainOpacityOverTime(uint initialalpha, uint finalalpha, uint transitionmilisec);
	void GainOpacityOverTime(uint finalalpha, uint transitionmilisec); //Starts at actual alpha
	void LossOpacityOverTime(uint initialalpha, uint finalalpha, uint transitionmilisec);
	void LossOpacityOverTime(uint finalalpha, uint transitionmilisec); //Starts at actual alpha

	void Focusable(bool value);
	bool FocusableStat() const;

	AddGuiTo GetPurpose() const;
	bool InFOV();
	bool PointContained(int x, int y) const;
	void CheckInput(const Gui* mouse_hover, const Gui* focus);
	
	void SetListener(j1Module* module);
	void SetListener(MainScene* module);
	const j1Module* GetModuleListener() const;
	const MainScene* GetSceneListener() const;

	void SetParentWindow(GuiWindow* window);
	void SetParentViewport(GuiViewport* viewport);

protected:
	AddGuiTo purpose = AddGuiTo::regular_purpose;
	GuiType type = GuiType::null_GuiType;
	iPoint position = { 0,0 };
	fPoint drag_vel = { 0.0f, 0.0f };
	bool visible = true;
	bool movable = false;
	uint opacity = 255; //0-255
	bool can_focus = false;
	bool move_with_camera = false;
	SDL_Rect Gui_Collider = { 0,0,0,0 };
	
	bool mouse_inside = false;
	j1Module* module_listener = nullptr;
	MainScene* scene_listener = nullptr;

	GuiWindow* ParentWindow = nullptr;
	GuiViewport* ParentViewport = nullptr;
};

#endif // __GUI_H__