#pragma once
#include "GameEntity.h"
#include "Behaviour.h"

class Tower : public GameEntity
{
public:
	Tower(Texture2D& image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1.)
		:GameEntity(image, coordinates, rotation, scale)
	{
		Behaviour::GetInstance().Register(*this);//register for update and draw calls
	}
	~Tower() 
	{
		Behaviour::GetInstance().Unregister(*this);
	};
};

