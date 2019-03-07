#include "pch.h"
#include "Tower.h"
#include "ResourceLoader.h"

Tower::TowerType Tower::GetTowerType()
{
	return towerType;
}

float Tower::GetRange()
{
	return range;
}

float Tower::GetDelay()
{
	return delay;
}

int Tower::GetDamage()
{
	return baseDamage;
}

void Tower::LevelUpgrade()
{
	level++;
	//update range, delay and basedamage
}

void Tower::hitTarget()
{

	if (m_target) {

		//float ammo_rotation;
		float ammoDistToTarget = hypot(ammo.getLocation().x - m_target->getLocation().x,
			ammo.getLocation().y - m_target->getLocation().y);
		Vector2 ammoMoveVector = { (ammo.getLocation().x - m_target->getLocation().x)/ammoDistToTarget,
			(ammo.getLocation().y - m_target->getLocation().y)/ammoDistToTarget };

		if (ammoDistToTarget > 150) {

			ammo.Move(ammoMoveVector);
			ammoDistToTarget = hypot(ammo.getLocation().x - m_target->getLocation().x,
				ammo.getLocation().y - m_target->getLocation().y);

		}
		else {
			LOG("hit");
			ammo.setLocation(this->getLocation());
			m_target->updateHealth(baseDamage);
		}
	}
}

Mob * Tower::getTarget()
{	return m_target;	}

void Tower::setTarget(Mob * target)
{	m_target = target;	}

