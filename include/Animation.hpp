#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "SpriteSheet.hpp"

struct AnimFrame {
	uint32_t frameX = 0;
	uint32_t frameY = 0;
	uint32_t frameW = 1;
	uint32_t frameH = 1;
	float duration = 1 / 60.0f;
};

class Animation {
   private:
	const SpriteSheet* sheet;
	std::vector<AnimFrame> frames;
	LTimer timer;
	float totalTime;

   public:
	Animation(const SpriteSheet* sheet_);

	void AddFrame(const AnimFrame& frame);

	TexView GetCurrentFrame() const;
};

#endif	// ANIMATION_HPP
