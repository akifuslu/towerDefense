#include "pch.h"
#include "Player.h"


int Player::getGold()
{
	return gold;
}

void Player::addGold(int val)
{
	gold += val;
}
