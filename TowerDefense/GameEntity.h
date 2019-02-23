#pragma once

#include "pch.h"

class GameEntity
{
public:
	//Default constructor
	GameEntity(Vector2 coordinates = {0., 0.}, double scale = 1., double rotation = 0., std::string imageName = "")
		: location(coordinates), scale(scale), rotation(rotation), image(image)
	{}

	//Destructor
	~GameEntity()
	{}

	//Gets and Sets

	double getScale() { return scale; }
	void   setScale(double newScale) { scale = newScale; }

	double getRotation() { return rotation; }
	void   setRotation(double newRotation) { rotation = newRotation; }

	Vector2 getLocation() { return location; }
	void    setLocation(Vector2 newLocation) { location = newLocation; }

	std::string getImageName() { return image; }
	void        setImageName(std::string newImageName) { image = newImageName; }

	void Draw();

private:

	//Scale
	double scale;

	//Rotation radian
	double rotation;

	//Location on the (x, y) coordinate system
	Vector2 location;

	//Name of the entity image
	std::string image;

};