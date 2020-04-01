#pragma once

#include <string>
#include <SFML/Graphics/Texture.hpp>

struct Spritesheet
{
	sf::Texture sheet;
	std::string name;

	Spritesheet(sf::Texture& sheet, std::string const& name)
		:
		sheet{ sheet },
		name{ name }
	{

	}

	Spritesheet()
		:
		sheet(),
		name("NOT_SET")
	{

	}
};