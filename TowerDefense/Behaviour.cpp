#include "pch.h"
#include "Behaviour.h"
#include "Mob.h"

void Behaviour::addMob(Mob & mobToAdd)
{
	//int r = (rand() % 5);
	mobToAdd.setLane(2);
	mobToAdd.setCurrentTarget(0);
	mobs.push_back(mobToAdd);
}

void Behaviour::getLanesFromTxt(std::string filePath)
{
	std::ifstream newText;
	newText.open(filePath.c_str());

	std::string line;
	int corners;

	Vector2 vecTemp; char chrTemp;
	int curLane = 0;

	std::getline(newText, line);
	corners = std::stoi(line);

	//DEVELOP THIS
	//Get lines one by one
	while (std::getline(newText, line)) {
		
		std::stringstream ss(line);

		ss >> chrTemp >> vecTemp.x >> chrTemp >> chrTemp >> vecTemp.y >> chrTemp;

		pathLanes[curLane++].push_back(vecTemp);

	}
}

void Behaviour::Register(GameEntity & entity)
{
	entities.push_back(&entity);
}

void Behaviour::Unregister(GameEntity & entity)
{
	entities.remove(&entity);
}

void Behaviour::Update() {
	Vector2 speed = { 0, 0 };
/*	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->Move(speed);
	}*/
	//Instead of using standart for loops, use iterators for safety
	//auto stands for type inference, you may use the type instead (GameEntity* for this example)
	for (auto const& entity: entities) 
	{
		entity->Move(speed);
	}

	for (auto & mob : mobs)
	{
		Vector2 moveVector;
		moveVector.x = mob.getLocation().x - Behaviour::pathLanes[mob.getLane()][mob.getCurrentTarget()].x;
		moveVector.y = mob.getLocation().y - Behaviour::pathLanes[mob.getLane()][mob.getCurrentTarget()].y;

		float length = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

		moveVector.x /= length;
		moveVector.y /= length;

		moveVector.x *= mob.getSpeed();
		moveVector.y *= mob.getSpeed();
		mob.Move(moveVector);

		mob.Draw();
	}



}

void Behaviour::DrawEntities()
{
	for(auto const& entity : entities)
	{
		entity->Draw();
	}
}
