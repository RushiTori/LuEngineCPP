#ifndef LBUTTON_HPP
#define LBUTTON_HPP

#include "InputHandler.hpp"

struct LButton {
	void (*action)(LButton*);
	float x, y, w, h;

	MouseButton button;
	bool isMouseIn;

	LButton(float x_, float y_, float w_, float h_);
	LButton(const LVector& pos, float w_, float h_);
	LButton(const LVector& pos, const LVector& sizes);

	LButton(const Rectangle& rec);
	operator Rectangle() const;

	virtual ~LButton();

	virtual void Display(const LColor& col, uint8_t highlightAlpha) const;
	virtual void Update(const LVector& mousePos);
};

constexpr uint32_t t = sizeof(LButton);

#endif	// LBUTTON_HPP
