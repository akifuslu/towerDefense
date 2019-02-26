#pragma once

#include "pch.h"
#include "GameEntity.h"

class Behaviour
{
private:
	Behaviour() {};
	std::vector<GameEntity*> entities;
public:
	Behaviour(Behaviour const&) = delete;
	void operator=(Behaviour const&) = delete;

	static Behaviour& GetInstance() {
		static Behaviour instance;
		return instance;
	}
	
	void Register(GameEntity& entity);

	void Update();
};