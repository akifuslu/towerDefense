#pragma once
#include "GameEntity.h"
#include "Clickable.h"
#include "InputHandler.h"

class Towerspot : public GameEntity, public Clickable
{
public:
	Towerspot(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1.)
		:GameEntity(image, coordinates, rotation, scale) 
	{
		SetClickAreaType(Circle);
		UpdateClickArea(coordinates.x, coordinates.y, image->width, image->height);
		InputHandler::GetInstance().Register(*this);//register as clickable to get click events 
		full = false;
	}
	~Towerspot()
	{
		InputHandler::GetInstance().Unregister(*this);//remove from click event list 
	}
	bool IsFull();
	void SetFull(bool isFull);
	bool OnClick() override;
private:
	bool full;
};
