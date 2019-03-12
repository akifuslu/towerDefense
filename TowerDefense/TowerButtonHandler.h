#pragma once
#include "TowerButton.h"
#include "Towerspot.h"
#include "Tower.h"

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
	void ClearButtons();
	void ShowButtons(Towerspot& spot);
	void HideButtons();
	void BuildTower(Tower::TowerType towerType, const std::string& towerImage, float range, float delay, int baseDamage);
private:
	TowerButtonHandler() { currentSpot = NULL; };
	std::list<TowerButton*> towerButtons;
	Towerspot* currentSpot;
};

