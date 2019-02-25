#pragma once
#include "pch.h"

class Clickable
{
public:
	virtual void OnClick() = 0 {};
	enum ClickAreaType{Circle, Rect};
	void UpdateClickArea(int posX, int posY, int width, int height);
	void SetClickAreaType(ClickAreaType areaType);
	int GetClickAreaType();
	Rectangle GetRectangle();
	Vector2 GetCircleCenter();
	float GetRadius();
private:
	ClickAreaType clickAreaType = Circle;//default click area
	Rectangle rect;
	Vector2 circleCenter;
	float radius;
};

inline void Clickable::UpdateClickArea(int posX, int posY, int width, int height)
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

inline void Clickable::SetClickAreaType(ClickAreaType areaType)
{
	clickAreaType = areaType;
}

inline int Clickable::GetClickAreaType()
{
	return clickAreaType;
}

inline Rectangle Clickable::GetRectangle()
{
	return rect;
}

inline Vector2 Clickable::GetCircleCenter()
{
	return circleCenter;
}

inline float Clickable::GetRadius()
{
	return radius;
}

