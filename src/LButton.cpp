#include "LButton.hpp"

LButton::LButton(float x_, float y_, float w_, float h_)
	: action([]([[maybe_unused]] LButton* button) {}),
	  x(x_),
	  y(y_),
	  w(w_),
	  h(h_),
	  button(MOUSE_BUTTON_LEFT),
	  isMouseIn(false) {}

LButton::LButton(const LVector& pos, float w_, float h_) : LButton(pos.x, pos.y, w_, h_) {}

LButton::LButton(const LVector& pos, const LVector& sizes) : LButton(pos.x, pos.y, sizes.x, sizes.y) {}

LButton::LButton(const Rectangle& rec) : LButton(rec.x, rec.y, rec.width, rec.height) {}

LButton::operator Rectangle() const {
	return (Rectangle){
		.x = x,
		.y = y,
		.width = w,
		.height = h,
	};
}

LButton::~LButton() {}

void LButton::Display(const LColor& col, uint8_t highlightAlpha) const {
	DrawRectangleRec(*this, col);
	if (isMouseIn) DrawRectangleRec(*this, Fade(WHITE, highlightAlpha / 255.0f));
}

void LButton::Update(const LVector& mousePos) {
	isMouseIn = CheckCollisionPointRec(mousePos, *this);
	if (isMouseIn && InputHandler::GetMouseButtonState(button) == InputState::PRESSED) action(this);
}
