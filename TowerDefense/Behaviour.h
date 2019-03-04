#pragma once

#include "pch.h"
#include "GameEntity.h"
#include "Mob.h"

//Singleton behaviour class for updating towers and mobs
class Behaviour
{
private:
	Behaviour() {};

	//Entities we want to control
	std::list<GameEntity*> entities;
	
	//Mobs we want to control
	std::list<Mob> mobs;

	//Path lanes for mobs to walk
	std::array<std::vector<Vector2>, 5> pathLanes;

public:
	Behaviour(Behaviour const&) = delete;
	void operator=(Behaviour const&) = delete;

	static Behaviour& GetInstance() {
		static Behaviour instance;
		return instance;
	}

	//Add mob
	void addMob(Mob& mobToAdd);

	//Read lanes from txt file.
	void getLanesFromTxt(std::string filePath);
	
	//Registering an entity to entity vector
	void Register(GameEntity& entity);

	//Unregister from behaviour updates
	void Unregister(GameEntity& entity);

	//Updating the registered entities
	void Update();

	//Draw registered entities
	void DrawEntities();

};