#pragma once
#include "GameEntity.h"
#include "Mob.h"

class Tower : public GameEntity
{
public:
	enum TowerType { ARCHER, MAGIC };
public:
	Tower(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., float range = 0, float delay = 0, int baseDamage = 0)
		:GameEntity(image, coordinates, rotation, scale), range(range), delay(delay), baseDamage(baseDamage), level(1), m_target(NULL)
	{
	}

	~Tower() 
	{
	}

	Tower::TowerType GetTowerType();
	float GetRange();
	float GetDelay();
	int GetDamage();
	void LevelUpgrade();

	void hitTarget();

	Mob* getTarget();
	void setTarget(Mob* target);

private:
	TowerType towerType;
	float range;
	float delay;
	int baseDamage;
	int level;
	Mob* m_target;
};

