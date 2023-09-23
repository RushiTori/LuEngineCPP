#include "TextBox.hpp"

TextBox::TextBox(float x, float y, float w, float h, uint maxCharCount_, const string& alphabet)
	: TextBox((Rectangle){.x = x, .y = y, .width = w, .height = h}, maxCharCount_, alphabet) {}

TextBox::TextBox(const LVector& pos, float w, float h, uint maxCharCount_, const string& alphabet)
	: TextBox((Rectangle){.x = pos.x, .y = pos.y, .width = w, .height = h}, maxCharCount_, alphabet) {}

TextBox::TextBox(const Rectangle& rec, uint maxCharCount_, const string& alphabet_)
	: alphabet(alphabet_), body(rec), maxCharCount(maxCharCount_) {}

void TextBox::SetPos(const LVector& pos) {
	this->body.x = pos.x;
	this->body.y = pos.y;
}

void TextBox::Move(const LVector& vel) {
	this->body.x += vel.x;
	this->body.y += vel.y;
}

void TextBox::SetSizes(const LVector& sizes) {
	this->body.width = sizes.x;
	this->body.height = sizes.y;
}

void TextBox::SetBody(const Rectangle& rec) { this->body = rec; }

void TextBox::TrySetContent(const string& str) {
	this->writingCursor = 0;
	this->selectCursor = -1;
	this->content = "";
	for (uint i = 0; i < str.length(); i++) {
		if (this->alphabet.find(str[i]) >= this->alphabet.length()) continue;
		if (this->content.size() >= this->maxCharCount) break;

		this->content.insert(this->content.begin() + this->writingCursor, str.at(i));
		this->writingCursor++;
	}
}

string TextBox::GetSelection() const {
	if (this->selectCursor < 0) return "";
	if (this->writingCursor == this->selectCursor) return "";

	uint selectIdx = std::min(this->writingCursor, this->selectCursor);
	uint selectLen = std::max(this->writingCursor, this->selectCursor) - selectIdx;

	string selection = this->content.substr(selectIdx, selectLen);

	return selection;
}

string TextBox::GetContentStr() const { return this->content; }

long TextBox::GetContentInt(uint base) const { return std::stol(this->content, nullptr, base); }

ulong TextBox::GetContentUInt(uint base) const { return std::stoul(this->content, nullptr, base); }

float TextBox::GetContentFloat() const { return std::stof(this->content); }

void TextBox::MouseInteract(const LVector& mousePos) {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		this->isFocused = CheckCollisionPointRec(mousePos, this->body);
	}
	if (!this->isFocused) {
		this->selectCursor = -1;
		return;
	}
	// WIP
}

void TextBox::EraseChars(uint eraseIdx, uint eraseCount) {
	this->content.erase(this->content.begin() + eraseIdx, this->content.begin() + eraseIdx + eraseCount);
	this->selectCursor = -1;
	this->writingCursor = eraseIdx;
}

bool TextBox::EraseSelection() {
	if (this->selectCursor < 0) return false;
	uint eraseIdx = std::min(this->writingCursor, this->selectCursor);
	uint eraseCount = std::max(this->writingCursor, this->selectCursor) - eraseIdx;
	EraseChars(eraseIdx, eraseCount);
	return true;
}

void TextBox::AddChars(const string& str) {
	EraseSelection();
	for (uint i = 0; i < str.length(); i++) {
		if (this->alphabet.find(str[i]) >= this->alphabet.length()) continue;
		if (this->content.size() >= this->maxCharCount) break;

		this->content.insert(this->content.begin() + this->writingCursor, str.at(i));
		this->writingCursor++;
	}
}

bool RepeatedKeyInput(int key, float timeThreshold, int perSecond) {
	if (IsKeyPressed(key)) return true;
	if (!IsKeyDown(key)) return false;
	if (KeyboardKeyHoldTimers[key] < timeThreshold) return false;

	if (GetCustomFrameCount(KeyboardKeyHoldTimers[key], 1.0 / perSecond) ==
		GetCustomFrameCount(KeyboardKeyHoldTimers[key] - GetFrameTime(), 1.0 / perSecond)) {
		return false;
	}

	return true;
}

void TextBox::Update(const LVector& mousePos) {
	if (!this->isActive) {
		this->isFocused = false;
		return;
	}

	MouseInteract(mousePos);

	if (!this->isFocused) return;

	for (int key = GetKeyPressed(); key; key = GetKeyPressed()) {
		this->writingCursor = std::clamp(this->writingCursor, 0, (int)this->content.size() - 1);
		if ((key == KEY_HOME) || (key == KEY_PAGE_UP)) {
			if (IsShiftDown) {
				if (this->selectCursor < 0) this->selectCursor = this->writingCursor;
			} else {
				this->selectCursor = -1;
			}
			this->writingCursor = 0;
		} else if ((key == KEY_END) || key == (KEY_PAGE_DOWN)) {
			if (IsShiftDown) {
				if (this->selectCursor < 0) this->selectCursor = this->writingCursor;
			} else {
				this->selectCursor = -1;
			}
			this->writingCursor = this->content.size() - 1;
		} else if (key == KEY_C) {
			if (IsCtrlDown) {
				string selection = GetSelection();
				if (selection.length()) {
					SetClipboardText(selection.c_str());
				}
				continue;
			}
		} else if (key == KEY_X) {
			if (IsCtrlDown) {
				string selection = GetSelection();
				if (selection.length()) {
					SetClipboardText(selection.c_str());
					EraseSelection();
				}
				continue;
			}
		} else if (key == KEY_V) {
			if (IsCtrlDown) {
				const char* clipText = GetClipboardText();
				AddChars(clipText);
				continue;
			}
		}

		char c = GetCharFromKey(key);
		if (c) AddChars("" + c);
	}

	if (this->content.size() <= 1) return;

	if (RepeatedKeyInput(KEY_BACKSPACE, 0.160, 16)) {
		if (!EraseSelection()) EraseChars(--this->writingCursor, 1);
	} else if (RepeatedKeyInput(KEY_DELETE, 0.160, 16)) {
		if (!EraseSelection() && (this->writingCursor < (int)this->content.size() - 1)) {
			EraseChars(this->writingCursor, 1);
		}
	}

	if (RepeatedKeyInput(KEY_LEFT, 0.160, 16)) {
		if (IsShiftDown) {
			if (this->selectCursor < 0) this->selectCursor = this->writingCursor;
			this->writingCursor--;
		} else if (this->selectCursor >= 0) {
			this->writingCursor = std::min(this->writingCursor, this->selectCursor);
			this->selectCursor = -1;
		} else {
			this->writingCursor--;
		}
	} else if (RepeatedKeyInput(KEY_RIGHT, 0.160, 16)) {
		if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
			if (this->selectCursor < 0) this->selectCursor = this->writingCursor;
			this->writingCursor++;
		} else if (this->selectCursor >= 0) {
			this->writingCursor = std::max(this->writingCursor, this->selectCursor);
			this->selectCursor = -1;
		} else {
			this->writingCursor++;
		}
	}

	this->writingCursor = std::clamp(this->writingCursor, 0, (int)this->content.size() - 1);

	if (this->writingCursor == this->selectCursor) this->selectCursor = -1;
}

float TextWidth(string text, uint n, float textSize) {
	if (text.empty()) return 0;

	n = std::min(n, (uint)text.length());
	if (n == text.length()) return MeasureTextEx(GetFontDefault(), text.c_str(), textSize, (int)(textSize / 10)).x;

	char temp = text[n];
	text[n] = '\0';

	float result = MeasureTextEx(GetFontDefault(), text.c_str(), textSize, (int)(textSize / 10)).x;
	text[n] = temp;

	return result;
}

void TextBox::DisplayCursor() const {
	float cursorThickness = TextWidth("I", 1, this->body.height);
	cursorThickness /= 2;

	float cursorSize = this->body.height * 0.90;
	cursorSize *= mapValue(sin(GetTime() * 2) * sin(GetTime() * 2), 0, 1, 0.15, 1);

	float cursorY = this->body.y + (this->body.height * 0.525);

	float cursorX = this->body.x + TextWidth(this->content, this->writingCursor, this->body.height);

	DrawRectangle(cursorX + cursorThickness / 2, cursorY - cursorSize / 2, cursorThickness, cursorSize, LColor::BLACK);
}

void TextBox::Display() const {
	// WIP
	DrawRectangleRec(this->body, DARKGRAY);
	if (this->isFocused) DrawRectangleRec(this->body, Fade(LColor::WHITE, 0.2));

	if (!this->content.size()) return;
	DrawTextL(this->content, LVector(this->body.x, this->body.y), this->body.height, TextAlign::LEFT, TextAlign::CENTER,
			  RAYWHITE);

	if (!this->isFocused) return;
	DisplayCursor();
	if (this->selectCursor < 0) return;
	float cursorX = this->body.x + TextWidth(this->content.c_str(), this->writingCursor, this->body.height);
	float selectX = this->body.x + TextWidth(this->content.c_str(), this->selectCursor, this->body.height);
	DrawRectangle(std::min(cursorX, selectX), this->body.y + this->body.height * 0.05,
				  std::max(cursorX, selectX) - std::min(cursorX, selectX), this->body.height * 0.9, Fade(PINK, 0.2));
}
