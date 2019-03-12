#include "pch.h"
#include "InputHandler.h"
#include "TowerButtonHandler.h"

void InputHandler::Register(Clickable & entity)
{
	entities.push_back(&entity);
}

void InputHandler::Unregister(Clickable & entity)
{
	entities.remove(&entity);
}

void InputHandler::Clear()
{
	entities.clear();
}

void InputHandler::HandleClick(Vector2 mousePos)
{
	for (auto const& entity : entities)
	{
		switch (entity->GetClickAreaType())
		{
		case Clickable::Circle:
			if (CheckCollisionPointCircle(mousePos, entity->GetCircleCenter(), entity->GetRadius()))
			{
				if (entity->OnClick())//if click succesfull do not click other elements
					return;
			}
			break;
		case Clickable::Rect:
			if (CheckCollisionPointRec(mousePos, entity->GetRectangle()))
			{
				if (entity->OnClick())//if click succesfull do not click other elements
					return;
			}
			break;
		default:
			break;
		}
	}
	//if none clicked
	TowerButtonHandler::GetInstance().HideButtons();
}
