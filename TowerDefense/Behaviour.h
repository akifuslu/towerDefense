#pragma once

#include "pch.h"
#include "GameEntity.h"
#include "Mob.h"
#include "Tower.h"

//Singleton behaviour class for updating towers and mobs
class Behaviour
{
private:
	Behaviour() {};
	~Behaviour() 
	{
		for (auto & i : towers)
			delete i;

		for (unsigned int i = 0; i < mobs.size(); i++)
			delete mobs[i];

		towers.clear();
	};
	//Mobs we want to control
	std::vector<Mob*> mobs;

	//count of mobs in each wave
	std::vector<int> waveMobCount;
	int currentWave;

	//Towers we want to control
	std::list<Tower*> towers;

	//Path lanes for mobs to walk
	std::array<std::vector<Vector2>, 5> pathLanes;

	//set mobs active in current wave
	void StartWave();

	//
	int waitWave;

	int mobCounter;

public:
	Behaviour(Behaviour const&) = delete;
	void operator=(Behaviour const&) = delete;

	static Behaviour& GetInstance() {
		static Behaviour instance;
		return instance;
	}

	//Registering mobs to update behaviour
	void RegisterMob(Mob* entity);

	//Unregister from behaviour updates
	void UnregisterMob(Mob* entity);

	//Init waves on level
	void SetWaves(std::vector<int> waveMobs);

	//Read lanes from txt file.
	void getLanesFromTxt(std::string filePath);
	
	//Registering towers to update behaviour
	void RegisterTower(Tower* entity);

	//Unregister from behaviour updates
	void UnregisterTower(Tower* entity);

	//Updating the registered entities
	void Update();

	//Draw registered entities
	void DrawEntities();

	void MobCount();

	void ClearAll();
};