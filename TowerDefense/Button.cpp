#include "pch.h"
#include "Button.h"
#include "ResourceLoader.h"

bool Button::OnClick()
{
	if (!getStatus())//disabled button
		return false;
	switch (currentFunc)
	{
	case -1:
		LOG("No actions has been assigned for this button!");
		break;
	case 0:
		intFunc(intVal);
		break;
	case 1:
		strFunc(strVal);
		break;
	case 2:
		voidFunc();
		break;
	default:
		break;
	}
	return true;
}

void Button::Draw()
{
	if (getStatus() == false)
		return;
	GameEntity::Draw();//call base method
	DrawTextEx(DEFAULTFONT, text.c_str(), textPos, 30, 1, WHITE);
}

void Button::AddEvent(std::function<void(int)> func, int val)
{
	intFunc = func;
	intVal = val;
	currentFunc = 0;
}

void Button::AddEvent(std::function<void(const std::string&)> func, const std::string & val)
{
	strFunc = func;
	strVal = val;
	currentFunc = 1;
}

void Button::AddEvent(std::function<void()> func)
{
	voidFunc = func;
	currentFunc = 2;
}
