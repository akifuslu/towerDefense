#pragma once
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
private:
	Player(){};
	int gold;
};

