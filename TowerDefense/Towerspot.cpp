#include "pch.h"
#include "Towerspot.h"
#include "TowerButtonHandler.h"
#include "GameStateMachine.h"

bool Towerspot::IsFull()
{
	return full;
}

void Towerspot::SetFull(bool isFull, Tower* tower)
{
	full = isFull;
	spotTower = tower;
}

bool Towerspot::OnClick()
{
	if (!getStatus())//disabled button
		return false;
	if (GameStateMachine::GetInstance().OnPause())//game currently paused do not show buttons
		return false;
	TowerButtonHandler::GetInstance().HideButtons();
	if (full)
		TowerButtonHandler::GetInstance().ShowButtons(*this, *spotTower);
	else
		TowerButtonHandler::GetInstance().ShowButtons(*this);
	return true;
}

void Towerspot::Draw()
{
	if (!full)
		GameEntity::Draw();
}
