#pragma once

#include <SFML/System/Time.hpp>

#include <array>
#include <vector>
#include <string>

#include "Animation.h"
#include "AnimatedSprite.h"
#include "Spritesheets.h"

class AnimEditor
{
public:
	AnimEditor();

	void update(sf::Time const& deltaTime);
	 
private:
	void updateAnimPropsSubWindow();
	void updateSpritesheetSubWindow();
	void updateAnimationSubWindow();

private:
	/*std::vector<Animation> animations;
	std::array<char, 256> newAnimNameBuff;
	std::vector<std::array<char, 256>> changeAnimNameBuffs;*/

	std::vector<Animation> animations;
	int indexCurrentAnim;
	std::array<char, 256> animNameBuffer;
	Spritesheets& spritesheets;

	AnimatedSprite animSprite;
};

