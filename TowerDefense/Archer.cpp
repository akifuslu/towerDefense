#include "pch.h"
#include "Archer.h"

void Archer::hitTarget()
{
	if (!m_target || m_target->getLocation().y < 0)//no target
		return;
	isAttacking = true;
	projectile->setStatus(true);
	projectile->setLocation(this->getLocation());
}

void Archer::UpdateProjectile()
{
	if (!m_target)//no target
	{
		projectile->setLocation(getLocation());
		projectile->setStatus(false);
		isAttacking = false;
		return;
	}

	float dist = hypot(projectile->getLocation().x - m_target->getLocation().x,
		projectile->getLocation().y - m_target->getLocation().y);
	Vector2 moveVector = { (-projectile->getLocation().x + m_target->getLocation().x),
		(-projectile->getLocation().y + m_target->getLocation().y) };

	//normalize move vector
	float len = sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
	moveVector.x /= len;
	moveVector.y /= len;
	moveVector.x *= 4;
	moveVector.y *= 4;

	projectile->setRotation((180 / PI) * atan2(moveVector.y, moveVector.x));
	if (dist > 20) {
		projectile->Move(moveVector);
	}
	else {
		projectile->setStatus(false);
		m_target->updateHealth(baseDamage);
		/*
		LOG(projectile->getLocation().x << "," << projectile->getLocation().y);
		LOG(m_target->getHealth());
		*/
		isAttacking = false;
	}
}

void Archer::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();//call base method
	if (isAttacking)
		projectile->Draw();
}
