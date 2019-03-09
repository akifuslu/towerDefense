#include "pch.h"
#include "Tower.h"
#include "ResourceLoader.h"


float Tower::GetRange()
{
	return range;
}

int Tower::GetCooldown()
{
	return cooldown--;
}

void Tower::ResetCooldown()
{
	cooldown = delay;
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
	ResetCooldown();
}

Mob * Tower::getTarget()
{	return m_target;	}

void Tower::setTarget(Mob * target)
{	m_target = target;	}

bool Tower::IsAttacking()
{
	return isAttacking;
}

void Tower::UpdateProjectile()
{
	//will be overriden
}

void Tower::Draw()
{
	//will be overriden
}


