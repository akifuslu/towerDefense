#include "pch.h"
#include "TowerButton.h"
#include "TowerButtonHandler.h"


void TowerButton::OnClick()
{
	LOG(message);
	try 
	{
		TowerButtonHandler::GetInstance().BuildTower();
	}
	catch(std::string exception)
	{
		LOG(exception);
		return;
	}
	TowerButtonHandler::GetInstance().HideButtons();
}
