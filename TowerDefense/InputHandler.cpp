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
				entity->OnClick();
				return;//to avoid one click effect multiple clickables
			}
			break;
		case Clickable::Rect:
			if (CheckCollisionPointRec(mousePos, entity->GetRectangle()))
			{
				entity->OnClick();
				return;//to avoid one click effect multiple clickables
			}
			break;
		default:
			TowerButtonHandler::GetInstance().HideButtons();
			break;
		}
	}
	//if none clicked
	TowerButtonHandler::GetInstance().HideButtons();
}
