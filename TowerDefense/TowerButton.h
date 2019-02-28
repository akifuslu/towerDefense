#pragma once
#include "GameEntity.h"
#include "Clickable.h"
#include "InputHandler.h"

class TowerButton : public GameEntity, public Clickable
{
public:
	TowerButton(Texture2D& image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1.)
		:GameEntity(image, coordinates, rotation, scale)
	{
		SetClickAreaType(Rect);
		UpdateClickArea(coordinates.x, coordinates.y, image.width, image.height);
		InputHandler::GetInstance().Register(*this);//register as clickable to get click events 
	}
	~TowerButton()
	{
		InputHandler::GetInstance().Unregister(*this);//remove from click event list 
	}
	void OnClick() override;
private:
	std::string message;
//Getters and Setters
public:
	std::string GetMessage() { return message; }
	void SetMessage(const std::string& msg) { message = msg; }
};

