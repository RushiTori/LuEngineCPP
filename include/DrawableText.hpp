#ifndef DRAWABLE_TEXT_HPP
#define DRAWABLE_TEXT_HPP

#include <LuLibCPP/LuString.hpp>

#include "EngineUtils.hpp"

enum class TextAlign : uchar {
	CENTER = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 3,
	BOTTOM = 4,
};

struct DrawableText {
	string text;
	float textSize = 10;
	LColor textCol = LColor::WHITE;
	TextAlign textAlignX = TextAlign::LEFT, textAlignY = TextAlign::TOP;

	Rectangle body = (Rectangle){.x = 0, .y = 0, .width = (float)width, .height = (float)height};
	TextAlign bodyAlignX = TextAlign::CENTER, bodyAlignY = TextAlign::CENTER;

	DrawableText(const string& text_, float textSize_ = 10, LColor textCol_ = LColor::WHITE);

	void SetPos(const LVector& pos);
	void Move(const LVector& vel);
	void SetSizes(const LVector& sizes);
	void SetBody(const Rectangle& rec = (Rectangle){.x = 0, .y = 0, .width = (float)width, .height = (float)height});

	void SetTextAligns(TextAlign alignX = TextAlign::LEFT, TextAlign alignY = TextAlign::TOP);
	void SetBodyAligns(TextAlign alignX = TextAlign::CENTER, TextAlign alignY = TextAlign::CENTER);

	void Display() const;
};

void DrawTextL(const string& text, LVector pos, float size, TextAlign alignX, TextAlign alignY,
			   const LColor& col = LColor::WHITE);

template <typename T>
inline T GetAlignedOffset(T left, T center, T right, TextAlign align) {
	if ((align == TextAlign::LEFT) || (align == TextAlign::TOP)) return left;
	if ((align == TextAlign::RIGHT) || (align == TextAlign::BOTTOM)) return right;
	return center;
}

#endif	// DRAWABLE_TEXT_HPP
