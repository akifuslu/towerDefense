#pragma once
#include "pch.h"

class Clickable
{
public:
	virtual bool OnClick() = 0 {};
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
