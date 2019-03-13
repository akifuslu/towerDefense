#pragma once
#include "GameEntity.h"
#include "Mob.h"
#include "ResourceLoader.h"

class Tower : public GameEntity
{
public:
	enum TowerType { ARCHER, BOMBARD, MAGIC };
public:
	Tower(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., float range = 0, float delay = 0, int baseDamage = 0, int cost = 0)
		:GameEntity(image, coordinates, rotation, scale), range(range), delay(delay), baseDamage(baseDamage), level(1), m_target(NULL), upgradeCost(cost * 2)
	{
		isAttacking = false;
		cooldown = 0;
		level = 0;
	}

	~Tower() 
	{
	}

	float GetRange();
	int GetCooldown();
	void ResetCooldown();
	int GetDamage();
	virtual void LevelUpgrade();
	virtual void hitTarget();

	Mob* getTarget();
	void setTarget(Mob* target);

	bool IsAttacking();
	virtual void UpdateProjectile();
	void Draw() override;
	int GetUpgradeCost();
	
protected:
	int level;
	Mob* m_target;
	bool isAttacking;
	float range;
	int delay;
	int cooldown;
	int baseDamage;
	int upgradeCost;
};

