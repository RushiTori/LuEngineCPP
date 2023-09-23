#include "Button.hpp"

Button::Button(const Button& other)
	: onClick(other.onClick),
	  onHold(other.onHold),
	  onRelease(other.onRelease),
	  body(other.body),
	  button(other.button),
	  isMouseOn(other.isMouseOn),
	  isActive(other.isActive) {}

void Button::SetPos(const LVector& pos) {
	this->body.x = pos.x;
	this->body.y = pos.y;
}

void Button::Move(const LVector& vel) {
	this->body.x += vel.x;
	this->body.y += vel.y;
}

void Button::SetSizes(const LVector& sizes) {
	this->body.width = sizes.x;
	this->body.height = sizes.y;
}

void Button::SetBody(const Rectangle& rec) { this->body = rec; }

void Button::Update(const LVector& cursorPos) {
	this->isMouseOn = false;
	if (!this->isActive) return;
	this->isMouseOn = CheckCollisionPointRec(cursorPos, this->body);

	if (!this->isMouseOn) return;

	if (IsMouseButtonPressed(this->button)) {
		this->onClick();
	} else if (IsMouseButtonDown(this->button)) {
		this->onHold();
	} else if (IsMouseButtonReleased(this->button)) {
		this->onRelease();
	}
}

void Button::Display() const {
	DrawRectangleRec(this->body, GRAY);
	if (this->isActive) {
		if (this->isMouseOn) DrawRectangleRec(this->body, Fade(LColor::WHITE, 0.2));
	} else {
		DrawRectangleRec(this->body, Fade(LColor::BLACK, 0.2));
	}

	DrawRectangleLinesEx(this->body, 1, LColor::LU_PINK);
}
