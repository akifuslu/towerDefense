#pragma once
#include "Tower.h"

class Magic : public Tower
{
public:
	Magic(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., float range = 0, float delay = 0, int baseDamage = 0, int cost = 0)
		:Tower(image, coordinates, rotation, scale, range, delay, baseDamage, cost)
	{
		projectile = new GameEntity(GETTEXTURE("magic-beam"), { 0,0 }, 0, 1);
		projectile->setStatus(false);
		srcRect.height = GETTEXTURE("magic-beam")->height;
		srcRect.width = GETTEXTURE("magic-beam")->width;
		srcRect.x = projectile->getImage()->width;
		srcRect.y = 0;
		destRect.height = GETTEXTURE("magic-beam")->height;
		destRect.width = GETTEXTURE("magic-beam")->width;
	}
	~Magic() 
	{
		delete projectile;
	};
	void hitTarget() override;
	void UpdateProjectile() override;
	void Draw() override;
	GameEntity* getproj() { return projectile; }
private:
	GameEntity* projectile;
	Rectangle srcRect;
	Rectangle destRect;
	int frameCounter;
	int beamStartPos;
};

