#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Animation.h"

// Can play Animations
class AnimatedSprite
{
public:
	AnimatedSprite(sf::Vector2f const& position);

	void update(sf::Time const& deltaTime);
	void setAnimation(Animation* animation);
	sf::Sprite& getSprite();

private:
	Animation* anim;
	sf::Sprite sprite;

	int ellapsedMillis;
	int frameIndex;
};

