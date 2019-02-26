#include "pch.h"
#include "Towerspot.h"
#include "TowerButtonHandler.h"

bool Towerspot::IsFull()
{
	return full;
}

void Towerspot::OnClick()
{
	if (full)//TODO: if full check for demolition
		return;
	TowerButtonHandler::GetInstance().ShowButtons(*this);
}
