#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

#include "Animation/Spritesheets.h"
#include "Animation/Animation.h"
#include "Animation/AnimatedSprite.h"
#include "Animation/AnimEditor.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "ImGui + SFML = <3");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	bool showImguiWindow = true;
	sf::Color backgroundColor = sf::Color::Black;

	Spritesheets::getInstance().loadTextures();

	// DODGE_LEFT: (536, 1433, 37, 39), (580, 1435, 51, 37), (636, 1440, 45, 32), (685, 1439, 30, 33), (721, 1441, 34, 31), (759, 1425, 34, 47)

	Animation anim(&Spritesheets::getInstance().getSpritesheet("sora"), false, false, "RULL",
		200);
	anim.frames = 
	{
		sf::IntRect(536, 1433, 37, 39),
		sf::IntRect(580, 1435, 51, 37),
		sf::IntRect(636, 1440, 45, 32),
		sf::IntRect(685, 1439, 30, 33),
		sf::IntRect(721, 1441, 34, 31),
		sf::IntRect(759, 1425, 34, 47),
	}; 

	AnimatedSprite animSprite(sf::Vector2f(100, 100));
	animSprite.setAnimation(&anim);

	AnimEditor animEditor;

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}

		// Alle ImGui Widgets müssen zwischen Update() und Render() erstellt werden.
		sf::Time deltaTime = deltaClock.restart();
		ImGui::SFML::Update(window, deltaTime);

		ImGui::ShowDemoWindow();
		// animSprite.update(deltaTime);

		/*ImGui::Begin("Image window");

		ImGui::Image(animSprite.getSprite());

		ImGui::End();*/

		animEditor.update(deltaTime);

		window.clear(backgroundColor);

		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}