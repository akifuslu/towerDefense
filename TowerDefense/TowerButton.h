#pragma once
#include "GameEntity.h"
#include "Clickable.h"
#include "InputHandler.h"
#include "Tower.h"

class TowerButton : public GameEntity, public Clickable
{
public:
	TowerButton(Tower::TowerType towerType, const std::string& presetPath, const std::string& towerImage, Texture2D* image, Vector2 coordinates = { 0., 0. }, float rotation = 0., float scale = 1.)
		:GameEntity(image, coordinates, rotation, scale)
	{
		SetClickAreaType(Rect);
		UpdateClickArea(coordinates.x, coordinates.y, image->width, image->height);
		type = towerType;
		this->towerImage = towerImage;
		LoadPreset(presetPath);
		InputHandler::GetInstance().Register(*this);//register as clickable to get click events -
	}
	~TowerButton()
	{
		InputHandler::GetInstance().Unregister(*this);//remove from click event list 
	}
	void OnClick() override;
	void Draw() override;
private:
	void LoadPreset(const std::string& presetPath);
	Tower::TowerType type;
	float range;
	float delay;
	int baseDamage;
	int cost;
	std::string towerImage;
};

