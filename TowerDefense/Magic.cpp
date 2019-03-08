#include "pch.h"
#include "Magic.h"

void Magic::hitTarget()
{
	if (!m_target || m_target->getLocation().y < 0)//no target
		return;
	isAttacking = true;
	projectile->setStatus(true);
	projectile->setLocation(this->getLocation());
	frameCounter = 120;
}

void Magic::UpdateProjectile()
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

	projectile->setRotation((180 / PI) * atan2(moveVector.y, moveVector.x));
	destRect.x = projectile->getLocation().x;
	destRect.y = projectile->getLocation().y;
	srcRect.width = dist;
	destRect.width = dist;
	frameCounter--;
	if (frameCounter % 2 == 0)
	{
		srcRect.x -= 10;
		if (srcRect.x < 0)
			srcRect.x = projectile->getImage()->width;
	}
}

void Magic::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();//call base method
	if (isAttacking)
		DrawTexturePro(*(projectile->getImage()), srcRect, destRect, {0,0}, projectile->getRotation(), WHITE);
}
