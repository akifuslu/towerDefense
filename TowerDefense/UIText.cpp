#include "pch.h"
#include "UIText.h"
#include "ResourceLoader.h"

void UIText::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();
	Vector2 pos = getLocation();
	pos.x += relativePos.x;
	pos.y += relativePos.y;
	DrawTextEx(DEFAULTFONT, text.c_str(), pos, fontSize, 1, color);
}

void UIText::UpdateText(const std::string &text)
{
	this->text = text;
}
