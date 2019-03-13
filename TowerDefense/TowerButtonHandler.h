#pragma once
#include "TowerButton.h"
#include "Towerspot.h"
#include "Tower.h"
#include "Button.h"
#include "UIText.h"

class TowerButtonHandler
{
public:
	static TowerButtonHandler& GetInstance() 
	{
		static TowerButtonHandler instance;
		return instance;
	}
	TowerButtonHandler(TowerButtonHandler const&) = delete;
	void operator=(TowerButtonHandler const&) = delete;
	void AddButton(TowerButton& button);
	void AddButton(Button& button);
	void ClearButtons();
	void ShowButtons(Towerspot& spot);
	void ShowButtons(Towerspot& spot, Tower& tower);
	void HideButtons();
	void BuildTower(Tower::TowerType towerType, const std::string& towerImage, float range, float delay, int baseDamage, int cost);
	void UpgradeTower();
	void DestroyTower();
	UIText* upgradeText;
private:
	TowerButtonHandler() { currentSpot = NULL; };
	std::list<TowerButton*> towerButtons;
	std::list<Button*> buttons;
	Towerspot* currentSpot;
	Tower* currentTower;
};
