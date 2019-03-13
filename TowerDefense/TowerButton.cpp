#include "pch.h"
#include "TowerButton.h"
#include "TowerButtonHandler.h"
#include "Tower.h"
#include "ResourceLoader.h"
#include "Player.h"
#include "GameStateMachine.h"

bool TowerButton::OnClick()
{
	if (!getStatus())//disabled button
		return false;
	if (GameStateMachine::GetInstance().OnPause())//game currently paused do not build tower
		return false;
	if (Player::GetInstance().getGold() < cost)
	{
		LOG("not enough gold!");
		return false;
	}
	try 
	{
		TowerButtonHandler::GetInstance().BuildTower(type, towerImage, range, delay, baseDamage, cost);
		Player::GetInstance().addGold(-cost);//Reduce players gold
	}
	catch(std::string exception)
	{
		LOG(exception);
		return false;
	}
	TowerButtonHandler::GetInstance().HideButtons();
	return true;
}

void TowerButton::Draw()
{
	if (getStatus() == false)
		return;
	GameEntity::Draw();//call base method
	//now draw cost
	Vector2 coinPos = getLocation();
	coinPos.y -= 25;
	DrawTextureEx(*GETTEXTURE("coin"), coinPos, 0, 1, WHITE);
	DrawTextEx(DEFAULTFONT, std::to_string(cost).c_str(), { getLocation().x + 25, getLocation().y - 20 }, 15, 1, WHITE);
}

void TowerButton::LoadPreset(const std::string & presetPath)
{
	std::string line;
	std::ifstream presetFile(presetPath);
	if (presetFile.is_open())
	{
		//read range
		std::getline(presetFile, line);
		range = std::stof(line);
		//read delay
		std::getline(presetFile, line);
		delay = std::stof(line);
		//read damage
		std::getline(presetFile, line);
		baseDamage = std::atoi(line.c_str());
		//read cost
		std::getline(presetFile, line);
		cost = std::atoi(line.c_str());
	}
	else
		LOG("Tower preset couldn't found!");
}
