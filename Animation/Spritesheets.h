
#pragma once

#include <map>
#include <string>
#include <iostream>
#include <vector>

#include "Spritesheet.h"

class Spritesheets
{
public:
	static Spritesheets& getInstance()
	{
		static Spritesheets instance;
		return instance;
	}

	void loadTextures()
	{
		sheetPaths = 
		{
			{ "gothic_hero", "spritesheets/gothic-hero-run.png"},
		    { "sora", "spritesheets/khcom_sora_transparent.png" }
		};

		for (auto const& sheetPath : sheetPaths)
		{
			sf::Texture sheet;
			if (!sheet.loadFromFile(sheetPath.second))
			{
				std::cout << "Failed to load Texture at: " << sheetPath.second << std::endl;
				std::cin.get();
			}

			spritesheets[sheetPath.first] = Spritesheet(sheet, sheetPath.first);
		}
	}

	Spritesheet& getSpritesheet(std::string const& sheetName)
	{
		if (spritesheets.count(sheetName) == 0)
		{
			std::cout << "Failed to return Texture " << sheetName << std::endl;
			std::cin.get();
		}
		return spritesheets.at(sheetName);
	}

	std::vector<std::string> getSheetNames()
	{
		std::vector<std::string> sheetNames;
		for (auto const& sheet : spritesheets)
		{
			sheetNames.push_back(sheet.first);
		}
		return sheetNames;
	}

	int getNumSpritesheets()
	{
		return spritesheets.size();
	}

public:
	Spritesheets(Spritesheets const&) = delete;
	void operator=(Spritesheets const&) = delete;

private:
	Spritesheets() {}

private:
	// std::map<std::string, sf::Texture> textures;

	std::map<std::string, Spritesheet> spritesheets;
	std::map<std::string, std::string> sheetPaths;
};

