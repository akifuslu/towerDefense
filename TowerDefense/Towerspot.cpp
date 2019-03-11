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

void Towerspot::OnClick()
{
	if (GameStateMachine::GetInstance().OnPause())//game currently paused do not show buttons
		return;
	if (full)//TODO: if full check for demolition or upgrade
		return;
	TowerButtonHandler::GetInstance().ShowButtons(*this);
}
