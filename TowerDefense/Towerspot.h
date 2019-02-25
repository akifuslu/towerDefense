#pragma once
#include "GameEntity.h"
#include "Clickable.h"
#include "InputHandler.h"

class Towerspot : public GameEntity, public Clickable
{
public:
	Towerspot(Texture2D& image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1.)
		:GameEntity(image, coordinates, rotation, scale) 
	{
		SetClickAreaType(Circle);
		UpdateClickArea(coordinates.x, coordinates.y, image.width, image.height);
		InputHandler::GetInstance().Register(*this);//register as clickable to get click events 
	}
	bool IsFull();
	void OnClick() override;
private:
	bool full;
};
