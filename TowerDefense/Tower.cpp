#include "pch.h"
#include "Tower.h"

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

Mob * Tower::getTarget()
{	return m_target;	}

void Tower::setTarget(Mob * target)
{	m_target = target;	}

