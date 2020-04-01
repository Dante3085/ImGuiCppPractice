#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <string>

#include "Spritesheet.h"

// Specific pieces of information about a Spritesheet that make up an Animation.
class Animation
{
public:
	Animation
	(
		Spritesheet* tex = nullptr, 
		bool isLooped = false,
		bool isMirrored = false, 
		std::string const& name = "NO_NAME",
		int frameDelayMillis = 100
	);

	std::string toString() const;

public:
	Spritesheet* spritesheet;
	std::vector<sf::IntRect> frames;
	std::vector<sf::Vector2i> frameOffsets;
	bool isLooped;
	bool isMirrored;
	std::string name;
	int frameDelayMillis;
};

