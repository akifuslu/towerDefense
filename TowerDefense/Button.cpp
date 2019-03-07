#include "pch.h"
#include "Button.h"

void Button::OnClick()
{
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
}

void Button::Draw()
{
	if (getStatus() == false)
		return;
	GameEntity::Draw();//call base method
	Vector2 textPos = getLocation();
	textPos.x += getImage()->width / 3;
	textPos.y += getImage()->height / 3;
	DrawText(text.c_str(), textPos.x, textPos.y, 25, WHITE);
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
