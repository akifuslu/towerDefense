#include "pch.h"
#include "Mob.h"
#include "Player.h"
#include "ResourceLoader.h"

//Getters & Setters

int   Mob::getHealth() { return m_health; }
void  Mob::updateHealth(int damage)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		m_health = 0;
		if (!m_isDead)
		{
			m_isDead = true;
			Player::GetInstance().addGold(m_cost);
			setImage(ResourceLoader::GetInstance().GetTexture("mobdead"));
		}
	}
}

float Mob::getSpeed() const { return m_speed; }
void  Mob::setSpeed(float newSpeed) { m_speed = newSpeed; }

int   Mob::getLane() const { return m_lane; }
void  Mob::setLane(int newLane) { m_lane = newLane; }

int   Mob::getCurrentTarget() const { return m_currentTarget; }
void  Mob::setCurrentTarget(int newTarget) { m_currentTarget = newTarget; }