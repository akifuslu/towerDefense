#pragma once

#include "pch.h"
#include "GameEntity.h"

//Singleton behaviour class for updating towers and mobs
class Behaviour
{
private:
	Behaviour() {};

	//Entities we want to control
	std::list<GameEntity*> entities;

public:
	Behaviour(Behaviour const&) = delete;
	void operator=(Behaviour const&) = delete;

	static Behaviour& GetInstance() {
		static Behaviour instance;
		return instance;
	}
	
	//Registering an entity to entity vector
	void Register(GameEntity& entity);

	//Unregister from behaviour updates
	void Unregister(GameEntity& entity);

	//Updating the registered entities
	void Update();

	//Draw registered entities
	void DrawEntities();

};