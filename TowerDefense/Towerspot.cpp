#include "pch.h"
#include "Towerspot.h"
#include "TowerButtonHandler.h"
#include "GameStateMachine.h"

bool Towerspot::IsFull()
{
	return full;
}

void Towerspot::SetFull(bool isFull)
{
	full = isFull;
}

bool Towerspot::OnClick()
{
	if (!getStatus())//disabled button
		return false;
	if (GameStateMachine::GetInstance().OnPause())//game currently paused do not show buttons
		return false;
	if (full)//TODO: if full check for demolition or upgrade
		return false;
	TowerButtonHandler::GetInstance().ShowButtons(*this);
	return true;
}
