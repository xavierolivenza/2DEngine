#include "GuiViewport.h"
#include "j1Gui.h"

GuiViewport::GuiViewport(SDL_Rect* position_size, bool movable, bool can_focus, bool move_with_camera, j1Module* module_listener, AddGuiTo addto) :
	Gui({ position_size->x,position_size->y }, GuiType::gui_viewport, movable, can_focus, move_with_camera, module_listener, addto)
{
	Gui_Collider = { position_size->x,position_size->y,position_size->w,position_size->h };
	Viewport = Gui_Collider;
}

GuiViewport::GuiViewport(SDL_Rect* position_size, bool movable, bool can_focus, bool move_with_camera, MainScene* scene_listener, AddGuiTo addto) :
	Gui({ position_size->x,position_size->y }, GuiType::gui_viewport, movable, can_focus, move_with_camera, scene_listener, addto)
{
	Gui_Collider = { position_size->x,position_size->y,position_size->w,position_size->h };
	Viewport = Gui_Collider;
}

GuiViewport::~GuiViewport()
{

}

void GuiViewport::Update(const Gui* mouse_hover, const Gui* focus)
{
	Viewport.x = Gui_Collider.x;
	Viewport.y = Gui_Collider.y;
}

void GuiViewport::Draw()
{
	if (this->visible)
	{
		//Viewport items
		SDL_RenderSetViewport(App->render->renderer, &Viewport);
		for (std::list<Gui*>::iterator item = ViewportElements.begin(); item != ViewportElements.cend(); ++item)
			(*item)->Draw();
		SDL_RenderSetViewport(App->render->renderer, NULL);
		//Border
		App->render->DrawQuad(Viewport, White(0), White(1), White(2), 255, false, false);
		if (App->gui->isDebugDrawActive())
			this->DebugDraw();
	}
}

void GuiViewport::DebugDraw() const
{
	App->render->DrawQuad(Gui_Collider, GuiViewportDebugColor(0), GuiViewportDebugColor(1), GuiViewportDebugColor(2), DEBUG_DRAW_ALPHA, true, false, false);
}

void GuiViewport::push_back_item(Gui* newitem)
{
	ViewportElements.push_back(newitem);
	newitem->SetParentViewport(this);
}