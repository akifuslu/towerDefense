#pragma once
#include "GameEntity.h"
#include "Tower.h"


class Archer : public Tower
{
public:
	Archer(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., float range = 0, float delay = 0, int baseDamage = 0, int cost = 0)
		:Tower(image, coordinates, rotation, scale, range, delay, baseDamage, cost)
	{
		projectile = new GameEntity(GETTEXTURE("arrow"), { 0,0 }, 0, (float)0.03);
		projectile->setStatus(false);
	}
	~Archer() 
	{
		delete projectile;
	};
	void hitTarget() override;
	void UpdateProjectile() override;
	void Draw() override;
	void LevelUpgrade() override;
private:
	GameEntity * projectile;
	
};

