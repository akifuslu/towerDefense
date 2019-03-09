#include "pch.h"
#include "Bombard.h"

void Bombard::hitTarget()
{
	Tower::hitTarget();

	if (!m_target || m_target->getLocation().y < 0)//no target
		return;
	isAttacking = true;
	projectile->setStatus(true);
	projectile->setLocation({ this->getLocation().x + 20, this->getLocation().y});

	UpdateProjectile();
}

void Bombard::UpdateProjectile()
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
	moveVector.x *= 3;
	moveVector.y *= 3;

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
		frameCounter = 60;
		expPos = projectile->getLocation();
		expRect = 0;
	}
}

void Bombard::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();//call base method
	if (isAttacking)
		projectile->Draw();
	if (frameCounter > 0)
	{
		frameCounter--;
		if (frameCounter % 10 == 0)
			expRect += 96;
		DrawTextureRec(*GETTEXTURE("explosion"), { (float)expRect,0,96,96 }, { expPos.x - 40, expPos.y - 30}, WHITE);
	}
}