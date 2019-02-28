#include "pch.h"
#include "Behaviour.h"

void Behaviour::Register(GameEntity & entity)
{
	entities.push_back(&entity);
}

void Behaviour::Unregister(GameEntity & entity)
{
	entities.remove(&entity);
}

void Behaviour::Update() {
	Vector2 speed = { 0.1, 0.1 };
/*	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->Move(speed);
	}*/
	//Instead of using standart for loops, use iterators for safety
	//auto stands for type inference, you may use the type instead (GameEntity* for this example)
	for (auto const& entity: entities) 
	{
		entity->Move(speed);
	}
}

void Behaviour::DrawEntities()
{
	for(auto const& entity : entities)
	{
		entity->Draw();
	}
}
