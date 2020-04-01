#include "AnimatedSprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(sf::Vector2f const & position)
	:
	anim { nullptr },
	ellapsedMillis { 0 },
	frameIndex { 0 }
{
	sprite.setPosition(position);
}

void AnimatedSprite::update(sf::Time const & deltaTime)
{
	if (anim == nullptr || anim->frames.size() == 0)
		return;

	ellapsedMillis += deltaTime.asMilliseconds();
	if (ellapsedMillis >= anim->frameDelayMillis)
	{
		std::cout << "Frame " << frameIndex << std::endl;

		ellapsedMillis = 0;
		frameIndex = (frameIndex + 1) % anim->frames.size();
		sprite.setTextureRect(anim->frames[frameIndex]);
	}
}

void AnimatedSprite::setAnimation(Animation * animation)
{
	this->anim = animation;

	ellapsedMillis = 0;
	frameIndex = 0;
	sprite.setTexture((anim->spritesheet)->sheet);

	if (anim->frames.size() > 0)
		sprite.setTextureRect(anim->frames[frameIndex]);
}

sf::Sprite & AnimatedSprite::getSprite()
{
	return sprite;
}
