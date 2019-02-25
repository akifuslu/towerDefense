#pragma once

#include "pch.h"

class GameEntity
{

public:

	//Entity Functions
	void Draw();
	void Move(Vector2& moveVector);

private:

	//Scale
	float m_scale;

	//Rotation radian
	float m_rotation;

	//Location on the (x, y) coordinate system
	Vector2 m_location;

	//Name of the entity image
	Texture2D& m_image;

public:
	//Default constructor
	GameEntity(Texture2D& image, Vector2 coordinates = {0., 0.}, float rotation = 0., float scale = 1.)
		: m_location(coordinates), m_scale(scale), m_rotation(rotation), m_image(image)
	{}

	//Destructor
	~GameEntity()
	{}


	//Getters and Setters

	float getScale() { return m_scale; }
	void   setScale(float newScale) { m_scale = newScale; }

	float getRotation() { return m_rotation; }
	void   setRotation(float newRotation) { m_rotation = newRotation; }

	Vector2 getLocation() { return m_location; }
	void    setLocation(const Vector2& newLocation) { m_location = newLocation; }

	Texture2D& getImage() { return m_image; }
	void      setImage(const Texture2D& newImage) { m_image = newImage; }

};