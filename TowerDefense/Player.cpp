#include "pch.h"
#include "Player.h"


int Player::getGold()
{
	return gold;
}

void Player::addGold(int val)
{
	gold += val;
	if(goldText)
		goldText->UpdateText("gold: " + std::to_string(gold));
}

void Player::setGoldText(UIText * text)
{
	goldText = text;
}
