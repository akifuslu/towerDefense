#include "pch.h"
#include "GameEntity.h"

void GameEntity::Draw()
{
	if (!m_active)
		return;
	if(m_image)//do not draw if NULL
		DrawTextureEx(*m_image, m_location, m_rotation, m_scale, WHITE);
}

void GameEntity::Move(Vector2& moveVector)
{
	if (!m_active)
		return;
	m_location.x += moveVector.x;
	m_location.y += moveVector.y;
}
