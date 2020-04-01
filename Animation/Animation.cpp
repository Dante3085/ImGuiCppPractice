
#include "Animation.h"

Animation::Animation(Spritesheet* sheet, bool isLooped, bool isMirrored, std::string const& name, 
	                 int frameDelayMillis)
	:
	spritesheet{ sheet },
	frames { },
	frameOffsets { },
	isLooped { isLooped },
	isMirrored { isMirrored },
	name { name },
	frameDelayMillis { frameDelayMillis }
{
}

std::string Animation::toString() const
{
	using namespace std;

	std::string str = "Animation{ name: " + name + ", spritesheet: " + spritesheet->name +
		", frames: " + to_string(frames.size()) + ", frameOffsets: " + to_string(frameOffsets.size()) +
		", isLooped: " + to_string(isLooped) + ", isMirrored: " + to_string(isMirrored) +
		", frameDelayMillis: " + to_string(frameDelayMillis) + " }";

	return str;
}
