#include "pch.h"
#include "Clickable.h"

void Clickable::UpdateClickArea(int posX, int posY, int width, int height)
{
	switch (clickAreaType)
	{
	case Circle:
		radius = width / 2;
		circleCenter.x = posX + radius;
		circleCenter.y = posY + radius;
		break;
	case Rect:
		rect.x = posX;
		rect.y = posY;
		rect.width = width;
		rect.height = height;
	default:
		break;
	}
}

void Clickable::SetClickAreaType(ClickAreaType areaType)
{
	clickAreaType = areaType;
}

int Clickable::GetClickAreaType()
{
	return clickAreaType;
}

Rectangle Clickable::GetRectangle()
{
	return rect;
}

Vector2 Clickable::GetCircleCenter()
{
	return circleCenter;
}

float Clickable::GetRadius()
{
	return radius;
}


