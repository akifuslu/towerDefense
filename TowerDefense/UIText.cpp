#include "pch.h"
#include "UIText.h"

void UIText::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();
	Vector2 pos = getLocation();
	pos.x += relativePos.x;
	pos.y += relativePos.y;
	DrawText(text.c_str(), pos.x, pos.y, fontSize, color);
}

void UIText::UpdateText(const std::string &text)
{
	this->text = text;
}
