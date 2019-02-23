#pragma once

#include "pch.h"

class GameEntity
{

public:
	void Draw();

private:

	//Scale
	double m_scale;

	//Rotation radian
	double m_rotation;

	//Location on the (x, y) coordinate system
	Vector2 m_location;

	//Name of the entity image
	std::string m_image;

public:
	//Default constructor
	GameEntity(Vector2 coordinates = {0., 0.}, double scale = 1., double rotation = 0., std::string imageName = "")
		: m_location(coordinates), m_scale(scale), m_rotation(rotation), m_image(imageName)
	{}

	//Destructor
	~GameEntity()
	{}


	//Gets and Sets

	double getScale() { return m_scale; }
	void   setScale(double newScale) { m_scale = newScale; }

	double getRotation() { return m_rotation; }
	void   setRotation(double newRotation) { m_rotation = newRotation; }

	Vector2 getLocation() { return m_location; }
	void    setLocation(Vector2 newLocation) { m_location = newLocation; }

	std::string getImageName() { return m_image; }
	void        setImageName(std::string newImageName) { m_image = newImageName; }

};