#include "pch.h"
#include "GameEntity.h"

void GameEntity::Draw()
{
	DrawTextureEx(m_image, m_location, m_rotation, m_scale, WHITE);
}
