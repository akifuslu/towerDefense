#pragma once

#include "pch.h"
#include "GameEntity.h"

class Mob : public GameEntity
{
public:

	Mob(Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1., float speed = 100., int health = 100, int cost = 250)
		: GameEntity(image, coordinates, rotation, scale), m_speed(speed), m_health(health), m_isDead(false), m_cost(cost)
	{}

	//Getters & Setters
	
	int  getHealth();
	void updateHealth(int damage);

	float getSpeed() const;
	void  setSpeed(float newSpeed);

	int  getLane() const;
	void setLane(int newLane);

	int  getCurrentTarget() const;
	void setCurrentTarget(int newTarget);

private:

	bool m_isDead;

	int m_cost;

	//Current Health
	int m_health;

	//Current speed
	float m_speed;

	//There are 5 lanes in a road for each mob to follow. Since physics has not been used in this project, collision problem is solved with this.
	int m_lane;

	//The path is divided into corner targets. This is the current one.
	int m_currentTarget;
};