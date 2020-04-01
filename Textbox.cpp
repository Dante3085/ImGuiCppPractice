
#include "Textbox.h"

#include <iostream>

Textbox::Textbox(Rectangle const& posAndSize, sf::String const& content)
	:
	box{ posAndSize.getSize() },
	content { content },
	currentPage{ 0 },
	charDelayMillis{ 0 },
	ellapsedMillis{ 0 },
	waiting{ false }
{
	// Initialize box
	box.setFillColor(sf::Color::Red);
	box.setPosition(posAndSize.getPosition());

	// Create appropriate pages from content string.
	pages = strToPages(content);

	// Initialize visibleText.
	font.loadFromFile("fonts/arial.ttf");
	visibleText.setFont(font);
	visibleText.setCharacterSize(22);
	visibleText.setString(pages[currentPage][0]);
	visibleText.setPosition(box.getPosition());
}

void Textbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(box);
	target.draw(visibleText);
}

void Textbox::update(sf::Time const& deltaTime)
{
	if (!waiting)
	{
		ellapsedMillis += deltaTime.asMilliseconds();

		using namespace std;
		cout << ellapsedMillis << endl;

		if (ellapsedMillis >= charDelayMillis)
		{
			ellapsedMillis = 0;

		    // Append next character to visibleText
			sf::String updatedStr = visibleText.getString() + pages[currentPage][visibleText.getString().getSize()];
			visibleText.setString(updatedStr);

			// Finished writing current page ?
			// TODO: Better to compare strings or thei'r sizes ?
			if (updatedStr.getSize() == pages[currentPage].getSize())
			{
				waiting = true;
			}
		}
	}
	else
	{
		// TODO: Blink cursor and check forward/backward buttons.
	}
}

std::vector<sf::String> Textbox::strToPages(sf::String const & str)
{
	std::vector<sf::String> resultingPages;

	sf::Text text;
	sf::String page;
	for (int i = 0; i < str.getSize(); ++i)
	{
		append(text, str[i]);

		sf::FloatRect textBounds = text.getGlobalBounds();
		sf::FloatRect boxBounds = box.getGlobalBounds();

		if ((textBounds.left + textBounds.width) >= (boxBounds.left + boxBounds.width))
		{
			page += text.getString() + "\n";
			text.setString("");
		}
	}

	resultingPages.push_back(page);
	return resultingPages;
}

void Textbox::append(sf::Text & text, sf::String const& str)
{
	text.setString(text.getString() + str);
}
