#include "Gui.h"

#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "MainScene.h"

Gui::Gui(iPoint position, GuiType type, bool movable, AddGuiTo purpose)
{

}

void Gui::SetLocalPos(int x, int y)
{

}

iPoint Gui::GetLocalPos() const
{
	return{ 0, 0 };
}

void Gui::GetLocalPos(int& x, int& y) const
{

}

void Gui::Move(int x, int y)
{

}

void Gui::SetDragVelocity(float x, float y)
{

}

fPoint Gui::GetDragVelocity() const
{
	return{ 0.0f, 0.0f };
}

void Gui::GetDragVelocity(float& x, float& y) const
{

}

bool Gui::IsMovable() const
{
	return true;
}

void Gui::SetVisible(bool visible)
{

}

void Gui::SetOpacity(int alpha)
{

}

int Gui::GetOpacity() const
{
	return 0;
}

void Gui::SetOpacityOverTime(int initialalpha, int finalalpha, int transitionmilisec)
{

}

void Gui::SetOpacityOverTime(int finalalpha, int transitionmilisec)
{

}

void Gui::Focusable(bool value)
{

}

AddGuiTo Gui::GetPurpose() const
{
	return AddGuiTo::null_AddGuiTo;
}

bool Gui::InFOV()
{
	return true;
}

bool Gui::PointContained(int x, int y) const
{
	return true;
}

void Gui::CheckInput(const Gui* mouse_hover, const Gui* focus)
{

}

void Gui::SetListener(j1Module* module)
{

}

void Gui::SetListener(MainScene* module)
{

}

const j1Module* Gui::GetModuleListener() const
{
	return nullptr;
}

const MainScene* Gui::GetSceneListener() const
{
	return nullptr;
}