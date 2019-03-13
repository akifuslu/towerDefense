#include "pch.h"
#include "TowerButtonHandler.h"
#include "Tower.h"
#include "Archer.h"
#include "Magic.h"
#include "Bombard.h"
#include "ResourceLoader.h"
#include "Behaviour.h"
#include "Player.h"

void TowerButtonHandler::AddButton(TowerButton & button)
{
	towerButtons.push_back(&button);
}

void TowerButtonHandler::AddButton(Button & button)
{
	buttons.push_back(&button);
}

void TowerButtonHandler::ClearButtons()
{
	towerButtons.clear();
	buttons.clear();
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

void TowerButtonHandler::ShowButtons(Towerspot& spot, Tower& tower)
{
	currentTower = &tower;
	currentSpot = &spot;
	Vector2 startPos = tower.getLocation();
	startPos.x -= 15;
	startPos.y -= 30;
	upgradeText->setStatus(true);
	upgradeText->setLocation({startPos.x - 20, startPos.y - 30});
	upgradeText->UpdateText(std::to_string(tower.GetUpgradeCost()));
	for (Button* const& btn : buttons)
	{
		btn->setStatus(true);
		btn->setLocation(startPos);
		startPos.x += 50;
		btn->UpdateClickArea(btn->getLocation().x, btn->getLocation().y, btn->getImage()->width, btn->getImage()->height);
	}
}

void TowerButtonHandler::HideButtons()
{
	currentSpot = NULL;//no towerspot selected
	currentTower = NULL;//no tower selected
	for (TowerButton* const& btn : towerButtons)//hide buttons
	{
		btn->setStatus(false);
	}
	for (Button* const& btn : buttons)
	{
		btn->setStatus(false);
	}
	if(upgradeText)
		upgradeText->setStatus(false);
}

void TowerButtonHandler::BuildTower(Tower::TowerType towerType, const std::string& towerImage, float range, float delay, int baseDamage, int cost)
{
	if (!currentSpot)
		throw std::string("Null Pointer Exception!");
	//new tower will register itself for behaviour updates and it will be deleted by behaviour class
	Vector2 pos = currentSpot->getLocation();
	pos.x -= 12;
	pos.y -= 25;
	Tower* newTower;
	if (towerType == 0) {
		newTower = new Archer(GETTEXTURE(towerImage), pos, currentSpot->getRotation(), 0.4f, range, delay, baseDamage, cost);
		Behaviour::GetInstance().RegisterTower(newTower);
	}
	else if (towerType == 1) {
		newTower = new Bombard(GETTEXTURE(towerImage), pos, currentSpot->getRotation(), 0.4f, range, delay, baseDamage, cost);
		Behaviour::GetInstance().RegisterTower(newTower);
	}
	else {
		newTower = new Magic(GETTEXTURE(towerImage), pos, currentSpot->getRotation(), 0.4f, range, delay, baseDamage, cost);
		Behaviour::GetInstance().RegisterTower(newTower);
	}
//	currentSpot->setStatus(false);
	currentSpot->SetFull(true, newTower);
	currentSpot = NULL;
}

void TowerButtonHandler::UpgradeTower()
{
	if (currentTower == NULL || Player::GetInstance().getGold() < currentTower->GetUpgradeCost())
		return;
	Player::GetInstance().addGold(-currentTower->GetUpgradeCost());
	currentTower->LevelUpgrade();
	HideButtons();
}

void TowerButtonHandler::DestroyTower()
{
	if (currentTower == NULL)
		return;
	Behaviour::GetInstance().UnregisterTower(currentTower);
	delete currentTower;
	currentTower = NULL;
	currentSpot->SetFull(false, NULL);
	HideButtons();
}

