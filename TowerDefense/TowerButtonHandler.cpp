#include "pch.h"
#include "TowerButtonHandler.h"

void TowerButtonHandler::AddButton(TowerButton & button)
{
	towerButtons.push_back(&button);
}

void TowerButtonHandler::ShowButtons(Towerspot & spot)
{
	Vector2 startPos = spot.getLocation();
	startPos.x -= 50;
	startPos.y -= 70;
	for (TowerButton* const& btn : towerButtons)
	{
		btn->setStatus(true);
		btn->setLocation(startPos);
		startPos.x += 65;
	}
}

void TowerButtonHandler::HideButtons()
{
	for (TowerButton* const& btn : towerButtons)
	{
		btn->setStatus(false);
	}
}

