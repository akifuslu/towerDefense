#include "pch.h"
#include "Behaviour.h"
#include "Mob.h"
#include "ResourceLoader.h"

void Behaviour::RegisterMob(Mob & mobToAdd)
{
	int r = (rand() % 5);
	mobToAdd.setLane(r);
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

	while (std::getline(newText, line)) {
		
		std::stringstream ss(line);

		for (int i = 0; i < corners; i++) {
			ss >> vecTemp.x >> chrTemp >> vecTemp.y >> chrTemp;
			pathLanes[curLane].push_back(vecTemp);
		}
		curLane++;
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

		if (mob->getHealth() <= 0) {
			//öldü.
			mob->setImage(ResourceLoader::GetInstance().GetTexture("mobdead"));
			//2-3 saniye dinlendirip deaktive et.
			break;
		}

		Vector2 moveVector;
		moveVector.x = pathLanes[mob->getLane()][mob->getCurrentTarget()].x - mob->getLocation().x;
		moveVector.y = pathLanes[mob->getLane()][mob->getCurrentTarget()].y - mob->getLocation().y;

		float length = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

		if (length < 1) {
			if (pathLanes[mob->getLane()].size() > (unsigned int)(mob->getCurrentTarget()+1))
			{
				mob->setCurrentTarget(mob->getCurrentTarget()+1);
				moveVector.x = pathLanes[mob->getLane()][mob->getCurrentTarget()].x - mob->getLocation().x;
				moveVector.y = pathLanes[mob->getLane()][mob->getCurrentTarget()].y - mob->getLocation().y;
				length = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
			}
			else
			{
				//player loses 1 point and mob refreshes
			}
		}

		moveVector.x /= length;
		moveVector.y /= length;

		moveVector.x *= mob->getSpeed();
		moveVector.y *= mob->getSpeed();
		mob->Move(moveVector);
	}

	for (auto & tower : towers)//To-Do: update all towers
	{


		if (tower->getTarget() == NULL) {

			//get new target

			for (auto & mob : mobs) {
				if (hypot(mob->getLocation().x - tower->getLocation().x,
					mob->getLocation().y - tower->getLocation().y) < tower->GetRange()) {
					tower->setTarget(mob);
				}
			}
		}
		else
		{
			float distToTarget = hypot(tower->getTarget()->getLocation().x - tower->getLocation().x,
				tower->getTarget()->getLocation().y - tower->getLocation().y);

			if (distToTarget > tower->GetRange()) {

				for (auto & mob : mobs) {
					if (hypot(mob->getLocation().x - tower->getLocation().x,
						mob->getLocation().y - tower->getLocation().y) < tower->GetRange()) {
						tower->setTarget(mob);
					}
				}
			}
		}
		if (tower->getTarget()) {
			tower->getTarget()->updateHealth(tower->GetDamage());
		}
	}
}

void Behaviour::DrawEntities()
{
	for(auto const& mob : mobs)//draw all mobs
	{
		if (mob->getStatus()) {
			mob->Draw();
			LOG(mob->getHealth());
		}
	}
	for (auto const& tower : towers)//draw all towers
	{
		tower->Draw();
	}
}
