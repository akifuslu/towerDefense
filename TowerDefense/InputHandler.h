#pragma once
#include "pch.h"
#include "Clickable.h"

class InputHandler
{
public:
	static InputHandler& GetInstance() 
	{
		static InputHandler instance;
		return instance;
	}
	InputHandler(InputHandler const&) = delete;
	void operator=(InputHandler const&) = delete;
	void Register(Clickable& entity);
	void HandleClick(Vector2 mousePos);
private:
	InputHandler(){};
	std::vector<Clickable*> entities;
};

inline void InputHandler::Register(Clickable & entity)
{
	entities.push_back(&entity);
}

inline void InputHandler::HandleClick(Vector2 mousePos)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		switch (entities[i]->GetClickAreaType())
		{
		case Clickable::Circle:
			if (CheckCollisionPointCircle(mousePos, entities[i]->GetCircleCenter(), entities[i]->GetRadius()))
			{
				entities[i]->OnClick();
			}
			break;
		case Clickable::Rect:
			if (CheckCollisionPointRec(mousePos, entities[i]->GetRectangle()))
			{
				entities[i]->OnClick();
			}
			break;
		default:
			break;
		}
	}
}
