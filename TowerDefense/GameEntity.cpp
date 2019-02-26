#include "pch.h"
#include "GameEntity.h"

void GameEntity::Draw()
{
	DrawTextureEx(m_image, m_location, m_rotation, m_scale, WHITE);
}

void GameEntity::Move(Vector2& moveVector)
{
	m_location.x += moveVector.x;
	m_location.y += moveVector.y;
}
