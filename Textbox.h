#pragma once

// SFML includes
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>

// Other includes
#include <vector>

// My includes
#include "Rectangle.h"

class Textbox : public sf::Drawable
{
	// public interface
public:
	Textbox(Rectangle const& posAndSize, sf::String const& content);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void update(sf::Time const& deltaTime);
	
	// private helper functions
private:
	std::vector<sf::String> strToPages(sf::String const& str);
	void append(sf::Text& text, sf::String const& str);

	// private data
private:
	sf::RectangleShape box;

	sf::Text visibleText;
	sf::Font font;
	sf::String content;
	std::vector<sf::String> pages;
	int currentPage;
	int charDelayMillis; // Delay in milliseconds that it takes for a char to be visible.
	int ellapsedMillis;
	bool waiting;
};

