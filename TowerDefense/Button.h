#pragma once
#include "GameEntity.h"
#include "Clickable.h"
#include "InputHandler.h"

class Button : public GameEntity, public Clickable
{
public:
	Button(const std::string& text, Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1.)
		:GameEntity(image, coordinates, rotation, scale)
	{
		this->text = text;
		SetClickAreaType(Rect);
		UpdateClickArea(coordinates.x, coordinates.y, image->width, image->height);
		InputHandler::GetInstance().Register(*this);//register as clickable to get click events -
	}
	~Button()
	{
		InputHandler::GetInstance().Unregister(*this);//remove from click event list 
	}
	void OnClick() override;
	void Draw() override;
	void AddEvent(std::function<void(int)> func, int val);
	void AddEvent(std::function<void(const std::string &)> func, const std::string &);
	void AddEvent(std::function<void()> func);
private:
	std::string text;
	std::function<void(int)> intFunc;
	std::function<void(const std::string &)> strFunc;
	std::function<void()> voidFunc;
	int currentFunc;//-1 for none, 0 int, 1 str, 2 void
	int intVal;
	std::string strVal;
};

