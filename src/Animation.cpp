#include "Animation.hpp"

Animation::Animation(const SpriteSheet* sheet_) : sheet(sheet_), frames({}), timer(), totalTime(0) {}

void Animation::AddFrame(const AnimFrame& frame) {
	frames.push_back(frame);
	if (frames.back().duration <= 0) frames.back().duration = 1 / 60.0f;
	totalTime += frames.back().duration;
}

TexView Animation::GetCurrentFrame() const {
	if (!sheet) return TexView();
	if (frames.empty()) return TexView();
	float animTime = std::fmod(timer.GetSeconds(), totalTime);
	for (const auto& a : frames) {
		animTime -= a.duration;
		if (animTime <= 0) return sheet->GetTexView(a.frameX, a.frameY, a.frameW, a.frameH);
	}
	return TexView();
}
