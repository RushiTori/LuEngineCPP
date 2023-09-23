#include "EngineUtils.hpp"

uint width = 800;
uint height = 480;
ulong frameCount = 0;
Camera2D globalCamera = {.offset = {.x = 0, .y = 0}, .target = {.x = 0, .y = 0}, .rotation = 0, .zoom = 1};

float KeyboardKeyPressTimers[349] = {0};
float KeyboardKeyHoldTimers[349] = {0};
float KeyboardKeyUpTimers[349] = {0};

float AndroidKeyPressTimers[83] = {0};
float AndroidKeyHoldTimers[83] = {0};
float AndroidKeyUpTimers[83] = {0};

float MouseButtonPressTimers[7] = {0};
float MouseButtonHoldTimers[7] = {0};
float MouseButtonUpTimers[7] = {0};

float GamepadButtonPressTimers[][MAX_GAMEPADS] = {
	[GAMEPAD_BUTTON_UNKNOWN] = {0},			 [GAMEPAD_BUTTON_LEFT_FACE_UP] = {0},
	[GAMEPAD_BUTTON_LEFT_FACE_RIGHT] = {0},	 [GAMEPAD_BUTTON_LEFT_FACE_DOWN] = {0},
	[GAMEPAD_BUTTON_LEFT_FACE_LEFT] = {0},	 [GAMEPAD_BUTTON_RIGHT_FACE_UP] = {0},
	[GAMEPAD_BUTTON_RIGHT_FACE_RIGHT] = {0}, [GAMEPAD_BUTTON_RIGHT_FACE_DOWN] = {0},
	[GAMEPAD_BUTTON_RIGHT_FACE_LEFT] = {0},	 [GAMEPAD_BUTTON_LEFT_TRIGGER_1] = {0},
	[GAMEPAD_BUTTON_LEFT_TRIGGER_2] = {0},	 [GAMEPAD_BUTTON_RIGHT_TRIGGER_1] = {0},
	[GAMEPAD_BUTTON_RIGHT_TRIGGER_2] = {0},	 [GAMEPAD_BUTTON_MIDDLE_LEFT] = {0},
	[GAMEPAD_BUTTON_MIDDLE] = {0},			 [GAMEPAD_BUTTON_MIDDLE_RIGHT] = {0},
	[GAMEPAD_BUTTON_LEFT_THUMB] = {0},		 [GAMEPAD_BUTTON_RIGHT_THUMB] = {0},
};

float GamepadButtonHoldTimers[][MAX_GAMEPADS] = {
	[GAMEPAD_BUTTON_UNKNOWN] = {0},			 [GAMEPAD_BUTTON_LEFT_FACE_UP] = {0},
	[GAMEPAD_BUTTON_LEFT_FACE_RIGHT] = {0},	 [GAMEPAD_BUTTON_LEFT_FACE_DOWN] = {0},
	[GAMEPAD_BUTTON_LEFT_FACE_LEFT] = {0},	 [GAMEPAD_BUTTON_RIGHT_FACE_UP] = {0},
	[GAMEPAD_BUTTON_RIGHT_FACE_RIGHT] = {0}, [GAMEPAD_BUTTON_RIGHT_FACE_DOWN] = {0},
	[GAMEPAD_BUTTON_RIGHT_FACE_LEFT] = {0},	 [GAMEPAD_BUTTON_LEFT_TRIGGER_1] = {0},
	[GAMEPAD_BUTTON_LEFT_TRIGGER_2] = {0},	 [GAMEPAD_BUTTON_RIGHT_TRIGGER_1] = {0},
	[GAMEPAD_BUTTON_RIGHT_TRIGGER_2] = {0},	 [GAMEPAD_BUTTON_MIDDLE_LEFT] = {0},
	[GAMEPAD_BUTTON_MIDDLE] = {0},			 [GAMEPAD_BUTTON_MIDDLE_RIGHT] = {0},
	[GAMEPAD_BUTTON_LEFT_THUMB] = {0},		 [GAMEPAD_BUTTON_RIGHT_THUMB] = {0},
};

float GamepadButtonUpTimers[][MAX_GAMEPADS] = {
	[GAMEPAD_BUTTON_UNKNOWN] = {0},			 [GAMEPAD_BUTTON_LEFT_FACE_UP] = {0},
	[GAMEPAD_BUTTON_LEFT_FACE_RIGHT] = {0},	 [GAMEPAD_BUTTON_LEFT_FACE_DOWN] = {0},
	[GAMEPAD_BUTTON_LEFT_FACE_LEFT] = {0},	 [GAMEPAD_BUTTON_RIGHT_FACE_UP] = {0},
	[GAMEPAD_BUTTON_RIGHT_FACE_RIGHT] = {0}, [GAMEPAD_BUTTON_RIGHT_FACE_DOWN] = {0},
	[GAMEPAD_BUTTON_RIGHT_FACE_LEFT] = {0},	 [GAMEPAD_BUTTON_LEFT_TRIGGER_1] = {0},
	[GAMEPAD_BUTTON_LEFT_TRIGGER_2] = {0},	 [GAMEPAD_BUTTON_RIGHT_TRIGGER_1] = {0},
	[GAMEPAD_BUTTON_RIGHT_TRIGGER_2] = {0},	 [GAMEPAD_BUTTON_MIDDLE_LEFT] = {0},
	[GAMEPAD_BUTTON_MIDDLE] = {0},			 [GAMEPAD_BUTTON_MIDDLE_RIGHT] = {0},
	[GAMEPAD_BUTTON_LEFT_THUMB] = {0},		 [GAMEPAD_BUTTON_RIGHT_THUMB] = {0},
};

static const uint KeyboardKeyCount = sizeof(KeyboardKeyPressTimers) / sizeof(*KeyboardKeyPressTimers);
static const uint AndroidKeyCount = sizeof(AndroidKeyPressTimers) / sizeof(*AndroidKeyPressTimers);
static const uint MouseButtonCount = sizeof(MouseButtonPressTimers) / sizeof(*MouseButtonPressTimers);
static const uint GamepadButtonCount = sizeof(GamepadButtonPressTimers) / sizeof(*GamepadButtonPressTimers);

void UpdateLuEngine() {
	frameCount++;
	UpdateInputsTimers();
	UpdateCameraLu(globalCamera);
}

void UpdateInputsTimers() {
	float deltaTime = GetFrameTime();

	for (uint i = 0; i < KeyboardKeyCount; i++) {
		KeyboardKeyPressTimers[i] += deltaTime;
		KeyboardKeyHoldTimers[i] += deltaTime;
		KeyboardKeyUpTimers[i] += deltaTime;

		if (IsKeyPressed(i)) {
			KeyboardKeyPressTimers[i] = 0;
			KeyboardKeyHoldTimers[i] = 0;
			KeyboardKeyUpTimers[i] = 0;
		}
		if (IsKeyDown(i)) {
			KeyboardKeyUpTimers[i] = 0;
		}
		if (IsKeyReleased(i)) {
			KeyboardKeyUpTimers[i] = 0;
			KeyboardKeyHoldTimers[i] = 0;
		}
		if (IsKeyUp(i)) {
			KeyboardKeyHoldTimers[i] = 0;
		}
	}

	for (uint i = 0; i < AndroidKeyCount; i++) {
		AndroidKeyPressTimers[i] += deltaTime;
		AndroidKeyHoldTimers[i] += deltaTime;
		AndroidKeyUpTimers[i] += deltaTime;

		if (IsKeyPressed(i)) {
			AndroidKeyPressTimers[i] = 0;
			AndroidKeyHoldTimers[i] = 0;
			AndroidKeyUpTimers[i] = 0;
		}
		if (IsKeyDown(i)) {
			AndroidKeyUpTimers[i] = 0;
		}
		if (IsKeyReleased(i)) {
			AndroidKeyUpTimers[i] = 0;
			AndroidKeyHoldTimers[i] = 0;
		}
		if (IsKeyUp(i)) {
			AndroidKeyHoldTimers[i] = 0;
		}
	}

	for (uint i = 0; i < MouseButtonCount; i++) {
		MouseButtonPressTimers[i] += deltaTime;
		MouseButtonHoldTimers[i] += deltaTime;
		MouseButtonUpTimers[i] += deltaTime;

		if (IsMouseButtonPressed(i)) {
			MouseButtonPressTimers[i] = 0;
			MouseButtonHoldTimers[i] = 0;
			MouseButtonUpTimers[i] = 0;
		}
		if (IsMouseButtonDown(i)) {
			MouseButtonUpTimers[i] = 0;
		}
		if (IsMouseButtonReleased(i)) {
			MouseButtonUpTimers[i] = 0;
			MouseButtonHoldTimers[i] = 0;
		}
		if (IsMouseButtonUp(i)) {
			MouseButtonHoldTimers[i] = 0;
		}
	}

	for (uint i = 0; i < GamepadButtonCount; i++) {
		for (uint padNum = 0; padNum < MAX_GAMEPADS; padNum++) {
			GamepadButtonPressTimers[i][padNum] += deltaTime;
			GamepadButtonHoldTimers[i][padNum] += deltaTime;
			GamepadButtonUpTimers[i][padNum] += deltaTime;

			if (IsGamepadButtonPressed(padNum, i)) {
				GamepadButtonPressTimers[i][padNum] = 0;
				GamepadButtonHoldTimers[i][padNum] = 0;
				GamepadButtonUpTimers[i][padNum] = 0;
			}
			if (IsGamepadButtonDown(padNum, i)) {
				GamepadButtonUpTimers[i][padNum] = 0;
			}
			if (IsGamepadButtonReleased(padNum, i)) {
				GamepadButtonUpTimers[i][padNum] = 0;
				GamepadButtonHoldTimers[i][padNum] = 0;
			}
			if (IsGamepadButtonUp(padNum, i)) {
				GamepadButtonHoldTimers[i][padNum] = 0;
			}
		}
	}
}

void UpdateCameraLu(Camera2D& cam) {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 camMove = GetMouseDelta();
		camMove = Vector2Scale(camMove, -1 / cam.zoom);
		cam.target = Vector2Add(cam.target, camMove);
	}

	float zoomAmount = GetMouseWheelMove() * 0.15f;

	if (zoomAmount != 0) {
		Vector2 mouseBefore = GetScreenToWorld2D(GetMousePosition(), cam);
		cam.zoom *= 1 + zoomAmount;
		Vector2 mouseAfter = GetScreenToWorld2D(GetMousePosition(), cam);
		Vector2 mouseDiff = Vector2Subtract(mouseBefore, mouseAfter);
		cam.target = Vector2Add(cam.target, mouseDiff);
	}
}

char GetCharFromKey(int key) {
	if (key >= KEY_KP_0 && key <= KEY_KP_9) return '0' + (key - KEY_KP_0);
	if (key >= KEY_A && key <= KEY_Z) return (key - KEY_A) + ((IsShiftDown) ? 'A' : 'a');
	if (key >= KEY_ZERO && key <= KEY_NINE) return ((IsShiftDown) ? "!@#$%^&*()" : "0123456789")[key - KEY_ZERO];

	if (key == KEY_COMMA) return (IsShiftDown) ? '<' : ',';
	if (key == KEY_PERIOD) return (IsShiftDown) ? '>' : '.';
	if (key == KEY_SLASH) return (IsShiftDown) ? '?' : '/';

	if (key == KEY_SEMICOLON) return (IsShiftDown) ? ':' : ';';
	if (key == KEY_APOSTROPHE) return (IsShiftDown) ? '"' : '\'';

	if (key == KEY_LEFT_BRACKET) return (IsShiftDown) ? '{' : '[';
	if (key == KEY_RIGHT_BRACKET) return (IsShiftDown) ? '}' : ']';
	if (key == KEY_BACKSLASH) return (IsShiftDown) ? '|' : '\\';

	if (key == KEY_GRAVE) return (IsShiftDown) ? '~' : '`';

	if (key == KEY_MINUS) return (IsShiftDown) ? '_' : '-';
	if (key == KEY_EQUAL) return (IsShiftDown) ? '+' : '=';

	if (key == KEY_KP_DECIMAL) return '.';
	if (key == KEY_KP_DIVIDE) return '/';
	if (key == KEY_KP_MULTIPLY) return '*';
	if (key == KEY_KP_SUBTRACT) return '-';
	if (key == KEY_KP_ADD) return '+';
	if (key == KEY_KP_EQUAL) return '=';

	return 0;  // not a querty key
}
