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
	if (!m_target)//no target
		return;
	isAttacking = true;
	projectile->setStatus(true);
	projectile->setLocation(this->getLocation());
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
	if (!m_target)//no target
		return;
	//float ammo_rotation;
	float dist = hypot(projectile->getLocation().x - m_target->getLocation().x,
		projectile->getLocation().y - m_target->getLocation().y);
	Vector2 moveVector = { (-projectile->getLocation().x + m_target->getLocation().x) / dist,
		(-projectile->getLocation().y + m_target->getLocation().y) / dist };
	moveVector.x *= 6;
	moveVector.y *= 6;

	if (dist > 10) {

		projectile->Move(moveVector);
	}
	else {
		projectile->setStatus(false);
		m_target->updateHealth(baseDamage);
		isAttacking = false;
	}
}

void Tower::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();//call base method
	if (isAttacking)
		projectile->Draw();
}

