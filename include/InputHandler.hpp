#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "EngineUtils.hpp"

enum InputState : uint8_t {
	PRESSED = 0,
	DOWN,
	RELEASED,
	UP,
};

namespace InputHandler {

void Reset();

void Update();

InputState GetKeyState(KeyboardKey key);
InputState GetMouseButtonState(MouseButton button);
InputState GetGamepadButtonState(GamepadButton button);

float TimeSinceKeyPressed(KeyboardKey key);
float TimeSinceKeyDown(KeyboardKey key);
float TimeSinceKeyUp(KeyboardKey key);

float TimeSinceMouseButtonPressed(MouseButton button);
float TimeSinceMouseButtonDown(MouseButton button);
float TimeSinceMouseButtonUp(MouseButton button);

float TimeSinceGamepadButtonPressed(GamepadButton button);
float TimeSinceGamepadButtonDown(GamepadButton button);
float TimeSinceGamepadButtonUp(GamepadButton button);

uint64_t FramesSinceKeyPressed(KeyboardKey key);
uint64_t FramesSinceKeyDown(KeyboardKey key);
uint64_t FramesSinceKeyUp(KeyboardKey key);

uint64_t FramesSinceMouseButtonPressed(MouseButton button);
uint64_t FramesSinceMouseButtonDown(MouseButton button);
uint64_t FramesSinceMouseButtonUp(MouseButton button);

uint64_t FramesSinceGamepadButtonPressed(GamepadButton button);
uint64_t FramesSinceGamepadButtonDown(GamepadButton button);
uint64_t FramesSinceGamepadButtonUp(GamepadButton button);

}  // namespace InputHandler

#endif	// INPUT_HANDLER_HPP
