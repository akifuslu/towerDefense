#pragma once
#include "Tower.h"

class Bombard : public Tower
{
public:
	Bombard(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., float range = 0, float delay = 0, int baseDamage = 0, int cost = 0)
		:Tower(image, coordinates, rotation, scale, range, delay, baseDamage, cost)
	{
		projectile = new GameEntity(GETTEXTURE("bomb"), { 0,0 }, 0, (float)0.1);
		projectile->setStatus(false);
		frameCounter = 0;
	}
	~Bombard() 
	{
		delete projectile;
	};
	void hitTarget() override;
	void UpdateProjectile() override;
	void Draw() override;
private:
	GameEntity * projectile;
	int frameCounter;
	Vector2 expPos;
	int expRect;
};

