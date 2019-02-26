#include "pch.h"
#include "Behaviour.h"

void Behaviour::Register(GameEntity & entity)
{
	entities.push_back(&entity);
}

void Behaviour::Update() {
	Vector2 speed = { 0.1, 0.1 };
	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->Move(speed);
	}
}