#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "EngineUtils.hpp"

using ButtonAction = std::function<void(void)>;

class Button {
   public:
	ButtonAction onClick = []() {}, onHold = []() {}, onRelease = []() {};
	Rectangle body = (Rectangle){.x = 0, .y = 0, .width = 275, .height = 30};
	MouseButton button = MOUSE_LEFT_BUTTON;
	bool isMouseOn = false, isActive = true;

	Button(const Rectangle& body_ = (Rectangle){.x = 0, .y = 0, .width = 275, .height = 30}) : body(body_) {}

	Button(const Button& other);

	virtual ~Button() = default;

	void SetPos(const LVector& pos);
	void Move(const LVector& vel);
	void SetSizes(const LVector& sizes);
	void SetBody(const Rectangle& rec = (Rectangle){.x = 0, .y = 0, .width = 275, .height = 30});

	virtual void Update(const LVector& cursorPos = GetMousePosition());
	virtual void Display() const;
};

#endif	// BUTTON_HPP
