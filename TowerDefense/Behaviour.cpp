#include "pch.h"
#include "Behaviour.h"
#include "Mob.h"
#include "GameStateMachine.h"
#include "Player.h"

void Behaviour::StartWave()
{
	for (int i = mobs.size() - 1; i > ((int)mobs.size() - waveMobCount[currentWave] - 1); i--)
	{
		mobs[i]->setStatus(true);
	}
}

void Behaviour::RegisterMob(Mob * mobToAdd)
{
	int r = (rand() % 5);
	int yOffset = (rand() % 100);
	mobToAdd->setLane(r);
	mobToAdd->setLocation({pathLanes[r][0].x, pathLanes[r][0].y - yOffset});
	mobToAdd->setCurrentTarget(0);
	mobs.push_back(mobToAdd);
}

void Behaviour::UnregisterMob(Mob * entity)
{
	//may be unnecessary
}

void Behaviour::SetWaves(std::vector<int> waveMobs)
{
	waveMobCount = waveMobs;
	currentWave = waveMobCount.size() - 1;
	for (unsigned int i = 0; i < mobs.size(); i++)
	{
		mobs[i]->setStatus(false);
	}
	StartWave();//start first wave
	waitWave = 180;
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

void Behaviour::RegisterTower(Tower * entity)
{
	towers.push_back(entity);
}

void Behaviour::UnregisterTower(Tower * entity)
{
	towers.remove(entity);
}

void Behaviour::Update() {
	//update all mobs, 
	//we will traverse backwards for better performance
	//(we may delete entities from vector, deleting from end cheaper)
	if (waitWave > 0)
	{
		waitWave--;
		return;
	}
	int mobCounter = 0;
	for (int i = mobs.size() - 1; i > (int)mobs.size() - waveMobCount[currentWave] - 1; i--)
	{
		if (!mobs[i]->getStatus())//amk pasifi
			continue;
		if (mobs[i]->getHealth() <= 0) {
			//öldü.
			mobCounter++;
			//2-3 saniye dinlendirip deaktive et.
			continue;
		}

		Vector2 moveVector;
		moveVector.x = pathLanes[mobs[i]->getLane()][mobs[i]->getCurrentTarget()].x - mobs[i]->getLocation().x;
		moveVector.y = pathLanes[mobs[i]->getLane()][mobs[i]->getCurrentTarget()].y - mobs[i]->getLocation().y;

		float length = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);

		if (length < 1) {
			if (pathLanes[mobs[i]->getLane()].size() > (unsigned int)(mobs[i]->getCurrentTarget()+1))
			{
				mobs[i]->setCurrentTarget(mobs[i]->getCurrentTarget()+1);
				moveVector.x = pathLanes[mobs[i]->getLane()][mobs[i]->getCurrentTarget()].x - mobs[i]->getLocation().x;
				moveVector.y = pathLanes[mobs[i]->getLane()][mobs[i]->getCurrentTarget()].y - mobs[i]->getLocation().y;
				length = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
			}
			else
			{
				//player loses 1 point and mob refreshes
				Player::GetInstance().loseHealth();
				mobs[i]->setStatus(false);

				mobCounter++;

				if (Player::GetInstance().getHealth() <= 0) {
					GameStateMachine::GetInstance().ExitGame();
				}
			}
		}

		moveVector.x /= length;
		moveVector.y /= length;

		moveVector.x *= mobs[i]->getSpeed();
		moveVector.y *= mobs[i]->getSpeed();
		mobs[i]->Move(moveVector);
	}

	//check if wave cleared
	if (mobCounter == waveMobCount[currentWave])
	{
		waitWave = 180;//wait three seconds for new wave
		int tmp = mobs.size();
		for (int i = mobs.size() - 1; i > tmp - waveMobCount[currentWave] - 1; i--)
		{ 
			mobs.erase(mobs.begin() + i);
		}

		for (auto & tower : towers)//To-Do: update all towers
		{
			/*tower->projectile->setLocation(tower->getLocation());
			tower->IsAttacking = false;*/

			tower->setTarget(NULL);
			tower->UpdateProjectile();
		
		}

		currentWave--;

		if (currentWave < 0)//re implement this
			GameStateMachine::GetInstance().ExitGame();
		else
			StartWave();
		return;
	}

	for (auto & tower : towers)//To-Do: update all towers
	{
		if (tower->IsAttacking())//already attacking
		{
			tower->UpdateProjectile();
			continue;
		}
		if (tower->GetCooldown() > 0)//cant attack right now
			continue;
		if (tower->getTarget() == NULL || tower->getTarget()->getHealth() <= 0) {

			if (tower->getTarget() && tower->getTarget()->getHealth() <= 0) {
				tower->setTarget(NULL);
			}

			//get new target
			for (int i = mobs.size() - 1; i > (int)mobs.size() - waveMobCount[currentWave] - 1; i--) {
				if (mobs[i]->getHealth() <= 0)
					continue;
				if (hypot(mobs[i]->getLocation().x - tower->getLocation().x,
					mobs[i]->getLocation().y - tower->getLocation().y) < tower->GetRange()) {
					tower->setTarget(mobs[i]);
				}
			}
		}
		else
		{
			float distToTarget = hypot(tower->getTarget()->getLocation().x - tower->getLocation().x,
				tower->getTarget()->getLocation().y - tower->getLocation().y);

			if (distToTarget > tower->GetRange()) {

				for (int i = mobs.size() - 1; i > (int)mobs.size() - waveMobCount[currentWave] - 1; i--) {
					if (hypot(mobs[i]->getLocation().x - tower->getLocation().x,
						mobs[i]->getLocation().y - tower->getLocation().y) < tower->GetRange() && mobs[i]->getHealth() > 0) {
						tower->setTarget(mobs[i]);
						break;
					}
				}
			}
		}
		tower->hitTarget();
	}
}

void Behaviour::DrawEntities()
{
	for(auto const& mob : mobs)//draw all mobs
	{
		if (mob->getStatus()) {
			mob->Draw();
		}
	}
	for (auto const& tower : towers)//draw all towers
	{
		tower->Draw();
	}
}
