#include "pch.h"
#include "Towerspot.h"

bool Towerspot::IsFull()
{
	return full;
}

void Towerspot::OnClick()
{
	LOG("Clicked on me!");
}
