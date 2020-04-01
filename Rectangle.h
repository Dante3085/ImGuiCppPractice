#pragma once

#include <SFML/System/Vector2.hpp>

class Rectangle
{
	// Functions
public:
	Rectangle(float x, float y, float width, float height);
	Rectangle(sf::Vector2f const& position, sf::Vector2f const& size);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	// Data
public:
	float x;
	float y;
	float width;
	float height;
};

