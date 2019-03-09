#include "pch.h"
#include "Magic.h"

void Magic::hitTarget()
{
	Tower::hitTarget();
	if (!m_target || m_target->getLocation().y < 0)//no target
		return;
	isAttacking = true;
	projectile->setStatus(true);
	projectile->setLocation({ getLocation().x + 30, getLocation().y+15 });
	frameCounter = 40;

	UpdateProjectile(); //glitch avoided
}

void Magic::UpdateProjectile()
{
	if (!m_target)//no target
	{
		projectile->setLocation({ getLocation().x, getLocation().y });
		projectile->setStatus(false);
		isAttacking = false;
		return;
	}

	float dist = hypot(projectile->getLocation().x - m_target->getLocation().x - 10,
		projectile->getLocation().y - m_target->getLocation().y - 10);
	Vector2 moveVector = { (-projectile->getLocation().x + m_target->getLocation().x),
		(-projectile->getLocation().y + m_target->getLocation().y) };

	projectile->setRotation((180 / PI) * atan2(moveVector.y, moveVector.x));
	destRect.x = projectile->getLocation().x;
	destRect.y = projectile->getLocation().y;
	srcRect.width = dist;
	destRect.width = dist;

	frameCounter--;

	if (frameCounter % 3 == 0)
	{
		srcRect.x -= 10;
		if (srcRect.x < 0)
			srcRect.x = projectile->getImage()->width;
	}
	if (frameCounter % 10 == 0)
		beamStartPos += 128;
	if (frameCounter == 0) {
		projectile->setStatus(false);
		m_target->updateHealth(baseDamage);
		isAttacking = false;
	}
}

void Magic::Draw()
{
	if (!getStatus())
		return;
	GameEntity::Draw();//call base method
	if (isAttacking) {
		DrawTexturePro(*(projectile->getImage()), srcRect, destRect, { 0,15 }, projectile->getRotation(), WHITE);
		DrawTexturePro(*GETTEXTURE("beam-start"), { (float)beamStartPos,0,128,128 }, { getLocation().x-16,getLocation().y - 36,96,96 }, {0,0}, 0, WHITE);
	}
}
