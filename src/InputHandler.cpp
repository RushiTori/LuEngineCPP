#include "InputHandler.hpp"

namespace InputHandler {

constexpr uint32_t KeyboardKeyCount = 349;
constexpr uint32_t MouseButtonCount = 7;
constexpr uint32_t GamepadButtonCount = 18;

static std::array<LTimer, KeyboardKeyCount> keyPressTimers;
static std::array<LTimer, KeyboardKeyCount> keyDownTimers;
static std::array<LTimer, KeyboardKeyCount> keyUpTimers;

static std::array<LTimer, MouseButtonCount> mousePressTimers;
static std::array<LTimer, MouseButtonCount> mouseDownTimers;
static std::array<LTimer, MouseButtonCount> mouseUpTimers;

static std::array<LTimer, GamepadButtonCount> gamepadPressTimers;
static std::array<LTimer, GamepadButtonCount> gamepadDownTimers;
static std::array<LTimer, GamepadButtonCount> gamepadUpTimers;

static std::array<uint64_t, KeyboardKeyCount> keyPressFrames;
static std::array<uint64_t, KeyboardKeyCount> keyDownFrames;
static std::array<uint64_t, KeyboardKeyCount> keyUpFrames;

static std::array<uint64_t, MouseButtonCount> mousePressFrames;
static std::array<uint64_t, MouseButtonCount> mouseDownFrames;
static std::array<uint64_t, MouseButtonCount> mouseUpFrames;

static std::array<uint64_t, GamepadButtonCount> gamepadPressFrames;
static std::array<uint64_t, GamepadButtonCount> gamepadDownFrames;
static std::array<uint64_t, GamepadButtonCount> gamepadUpFrames;

void Reset() {
	LTimer resetTimer;

	std::fill(keyPressTimers.begin(), keyPressTimers.end(), resetTimer);
	std::fill(keyDownTimers.begin(), keyDownTimers.end(), resetTimer);
	std::fill(keyUpTimers.begin(), keyUpTimers.end(), resetTimer);

	std::fill(mousePressTimers.begin(), mousePressTimers.end(), resetTimer);
	std::fill(mouseDownTimers.begin(), mouseDownTimers.end(), resetTimer);
	std::fill(mouseUpTimers.begin(), mouseUpTimers.end(), resetTimer);

	std::fill(gamepadPressTimers.begin(), gamepadPressTimers.end(), resetTimer);
	std::fill(gamepadDownTimers.begin(), gamepadDownTimers.end(), resetTimer);
	std::fill(gamepadUpTimers.begin(), gamepadUpTimers.end(), resetTimer);

	std::fill(keyPressFrames.begin(), keyPressFrames.end(), frameCount);
	std::fill(keyDownFrames.begin(), keyDownFrames.end(), frameCount);
	std::fill(keyUpFrames.begin(), keyUpFrames.end(), frameCount);

	std::fill(mousePressFrames.begin(), mousePressFrames.end(), frameCount);
	std::fill(mouseDownFrames.begin(), mouseDownFrames.end(), frameCount);
	std::fill(mouseUpFrames.begin(), mouseUpFrames.end(), frameCount);

	std::fill(gamepadPressFrames.begin(), gamepadPressFrames.end(), frameCount);
	std::fill(gamepadDownFrames.begin(), gamepadDownFrames.end(), frameCount);
	std::fill(gamepadUpFrames.begin(), gamepadUpFrames.end(), frameCount);
}

void Update() {
	for (uint32_t i = 0; i < KeyboardKeyCount; i++) {
		InputState currState = GetKeyState((KeyboardKey)i);

		if (currState == InputState::PRESSED) {
			keyPressTimers[i].Restart();
			keyPressFrames[i] = frameCount;
		}

		if (currState != InputState::DOWN) {
			keyDownTimers[i].Restart();
			keyDownFrames[i] = frameCount;
		}

		if (currState != InputState::UP) {
			keyUpTimers[i].Restart();
			keyUpFrames[i] = frameCount;
		}
	}
	
	for (uint32_t i = 0; i < MouseButtonCount; i++) {
		InputState currState = GetMouseButtonState((MouseButton)i);

		if (currState == InputState::PRESSED) {
			mousePressTimers[i].Restart();
			mousePressFrames[i] = frameCount;
		}

		if (currState != InputState::DOWN) {
			mouseDownTimers[i].Restart();
			mouseDownFrames[i] = frameCount;
		}

		if (currState != InputState::UP) {
			mouseUpTimers[i].Restart();
			mouseUpFrames[i] = frameCount;
		}
	}
	
	for (uint32_t i = 0; i < GamepadButtonCount; i++) {
		InputState currState = GetGamepadButtonState((GamepadButton)i);

		if (currState == InputState::PRESSED) {
			gamepadPressTimers[i].Restart();
			gamepadPressFrames[i] = frameCount;
		}

		if (currState != InputState::DOWN) {
			gamepadDownTimers[i].Restart();
			gamepadDownFrames[i] = frameCount;
		}

		if (currState != InputState::UP) {
			gamepadUpTimers[i].Restart();
			gamepadUpFrames[i] = frameCount;
		}
	}
}

InputState GetKeyState(KeyboardKey key) {
	if (IsKeyPressed(key)) return InputState::PRESSED;
	if (IsKeyReleased(key)) return InputState::RELEASED;
	if (IsKeyDown(key)) return InputState::DOWN;
	return InputState::UP;
}

InputState GetMouseButtonState(MouseButton button) {
	if (IsMouseButtonPressed(button)) return InputState::PRESSED;
	if (IsMouseButtonReleased(button)) return InputState::RELEASED;
	if (IsMouseButtonDown(button)) return InputState::DOWN;
	return InputState::UP;
}

InputState GetGamepadButtonState(GamepadButton button) {
	if (IsGamepadButtonPressed(0, button)) return InputState::PRESSED;
	if (IsGamepadButtonReleased(0, button)) return InputState::RELEASED;
	if (IsGamepadButtonDown(0, button)) return InputState::DOWN;
	return InputState::UP;
}

float TimeSinceKeyPressed(KeyboardKey key) { return keyPressTimers[key].GetSeconds(); }

float TimeSinceKeyDown(KeyboardKey key) { return keyDownTimers[key].GetSeconds(); }

float TimeSinceKeyUp(KeyboardKey key) { return keyUpTimers[key].GetSeconds(); }

float TimeSinceMouseButtonPressed(MouseButton button) { return mousePressTimers[button].GetSeconds(); }

float TimeSinceMouseButtonDown(MouseButton button) { return mouseDownTimers[button].GetSeconds(); }

float TimeSinceMouseButtonUp(MouseButton button) { return mouseUpTimers[button].GetSeconds(); }

float TimeSinceGamepadButtonPressed(GamepadButton button) { return gamepadPressTimers[button].GetSeconds(); }

float TimeSinceGamepadButtonDown(GamepadButton button) { return gamepadDownTimers[button].GetSeconds(); }

float TimeSinceGamepadButtonUp(GamepadButton button) { return gamepadUpTimers[button].GetSeconds(); }

uint64_t FramesSinceKeyPressed(KeyboardKey key) { return frameCount - keyPressFrames[key]; }

uint64_t FramesSinceKeyDown(KeyboardKey key) { return frameCount - keyDownFrames[key]; }

uint64_t FramesSinceKeyUp(KeyboardKey key) { return frameCount - keyUpFrames[key]; }

uint64_t FramesSinceMouseButtonPressed(MouseButton button) { return frameCount - mousePressFrames[button]; }

uint64_t FramesSinceMouseButtonDown(MouseButton button) { return frameCount - mouseDownFrames[button]; }

uint64_t FramesSinceMouseButtonUp(MouseButton button) { return frameCount - mouseUpFrames[button]; }

uint64_t FramesSinceGamepadButtonPressed(GamepadButton button) { return frameCount - gamepadPressFrames[button]; }

uint64_t FramesSinceGamepadButtonDown(GamepadButton button) { return frameCount - gamepadDownFrames[button]; }

uint64_t FramesSinceGamepadButtonUp(GamepadButton button) { return frameCount - gamepadUpFrames[button]; }

}  // namespace InputHandler
