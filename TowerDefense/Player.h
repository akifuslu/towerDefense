#pragma once
#include "UIText.h"

class Player
{
public:
	static Player& GetInstance()
	{
		static Player instance;
		return instance;
	}
	Player(Player const&) = delete;
	void operator=(Player const&) = delete;
	int getGold();
	void addGold(int val);
	void setGoldText(UIText* text);

	int getHealth();
	void setHealth(int val);
	void loseHealth();
	void setHealthText(UIText* text);
private:
	Player(){};
	int gold;
	UIText* goldText;
	int health;
	UIText* healthText;
};

