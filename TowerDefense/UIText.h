#pragma once
#include "GameEntity.h"

class UIText : public GameEntity
{
public:
	UIText(const std::string& text, int fontSize, Color color, Texture2D& image, Vector2 relativePos, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., bool active = true)
		: GameEntity(image, coordinates, rotation, scale, active)
	{
		this->text = text;
		this->fontSize = fontSize;
		this->color = color;
		this->relativePos = relativePos;
	};
	~UIText() {};
	void Draw() override;
	void UpdateText(const std::string &);
private:
	std::string text;
	int fontSize;
	Color color;
	Vector2 relativePos;
};

