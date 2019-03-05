#include "pch.h"
#include "Behaviour.h"
#include "Mob.h"

void Behaviour::RegisterMob(Mob & mobToAdd)
{
	//int r = (rand() % 5);
	mobToAdd.setLane(2);
	mobToAdd.setCurrentTarget(0);
	mobs.push_back(&mobToAdd);
}

void Behaviour::UnregisterMob(Mob & entity)
{
	mobs.remove(&entity);
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

void Behaviour::RegisterTower(Tower & entity)
{
	towers.push_back(&entity);
}

void Behaviour::UnregisterTower(Tower & entity)
{
	towers.remove(&entity);
}

void Behaviour::Update() {
	Vector2 speed = { 0, 0 };
	
	for (auto & mob : mobs)//update all mobs
	{
		Vector2 moveVector;
		moveVector.x = mob->getLocation().x - pathLanes[mob->getLane()][mob->getCurrentTarget()].x;
		moveVector.y = mob->getLocation().y - pathLanes[mob->getLane()][mob->getCurrentTarget()].y;

		float length = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

		moveVector.x /= length;
		moveVector.y /= length;

		moveVector.x *= mob->getSpeed();
		moveVector.y *= mob->getSpeed();
		mob->Move(moveVector);
	}

	for (auto & tower : towers);//To-Do: update all towers
}

void Behaviour::DrawEntities()
{
	for(auto const& mob : mobs)//draw all mobs
	{
		mob->Draw();
	}
	for (auto const& tower : towers)//draw all towers
	{
		tower->Draw();
	}
}
