#include "pch.h"
#include "TowerButtonHandler.h"
#include "Tower.h"
#include "Archer.h"
#include "Magic.h"
#include "ResourceLoader.h"
#include "Behaviour.h"

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
		btn->UpdateClickArea(btn->getLocation().x, btn->getLocation().y, btn->getImage()->width, btn->getImage()->height);
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

void TowerButtonHandler::BuildTower(Tower::TowerType towerType, const std::string& towerImage, float range, float delay, int baseDamage)
{
	if (!currentSpot)
		throw std::string("Null Pointer Exception!");
	//new tower will register itself for behaviour updates and it will be deleted by behaviour class
	Vector2 pos = currentSpot->getLocation();
	pos.x -= 12;
	pos.y -= 25;
	
	if (towerType == 0) {
		Behaviour::GetInstance().RegisterTower((new Archer(GETTEXTURE(towerImage), pos, currentSpot->getRotation(), 0.4f, range, delay, baseDamage)));
	}
	else if (towerType == 1) {

	}
	else {
		Behaviour::GetInstance().RegisterTower((new Magic(GETTEXTURE(towerImage), pos, currentSpot->getRotation(), 0.4f, range, delay, baseDamage)));
	}
	
	
	currentSpot->SetFull(true);
	currentSpot->setStatus(false);
	currentSpot = NULL;
}

