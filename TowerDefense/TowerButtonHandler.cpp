#include "pch.h"
#include "TowerButtonHandler.h"
#include "Tower.h"
#include "ResourceLoader.h"

void TowerButtonHandler::AddButton(TowerButton & button)
{
	towerButtons.push_back(&button);
}

void TowerButtonHandler::ShowButtons(Towerspot & spot)
{
	currentSpot = &spot;//save the spot for building tower
	//set buttons
	Vector2 startPos = spot.getLocation();
	startPos.x -= 50;
	startPos.y -= 70;
	for (TowerButton* const& btn : towerButtons)
	{
		btn->setStatus(true);
		btn->setLocation(startPos);
		startPos.x += 65;
		btn->UpdateClickArea(btn->getLocation().x, btn->getLocation().y, btn->getImage().width, btn->getImage().height);
	}
}

void TowerButtonHandler::HideButtons()
{
	currentSpot = NULL;//no towerspot selected
	//hide buttons
	for (TowerButton* const& btn : towerButtons)
	{
		btn->setStatus(false);
	}
}

void TowerButtonHandler::BuildTower()
{
	if (!currentSpot)
		throw std::string("Null Pointer Exception!");
	//new tower will register itself for behaviour updates and it will be deleted by behaviour class
	new Tower(GETTEXTURE("tower"), currentSpot->getLocation(), currentSpot->getRotation(), currentSpot->getScale());
}

