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

int Player::getHealth()
{
	return health;
}

void Player::setHealth(int val) {
	health = val;
	if (healthText)
		healthText->UpdateText("health: " + std::to_string(health));
}

void Player::loseHealth()
{
	health -= 1;
	if (healthText)
		healthText->UpdateText("health: " + std::to_string(health));
}

void Player::setHealthText(UIText * text)
{
	healthText = text;
}
