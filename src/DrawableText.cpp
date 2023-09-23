#include "DrawableText.hpp"

DrawableText::DrawableText(const string& text_, float textSize_, LColor textCol_)
	: text(text_), textSize(textSize_), textCol(textCol_) {}

void DrawableText::SetPos(const LVector& pos) {
	this->body.x = pos.x;
	this->body.y = pos.y;
}

void DrawableText::Move(const LVector& vel) {
	this->body.x += vel.x;
	this->body.y += vel.y;
}

void DrawableText::SetSizes(const LVector& sizes) {
	this->body.width = sizes.x;
	this->body.height = sizes.y;
}

void DrawableText::SetBody(const Rectangle& rec) { this->body = rec; }

void DrawableText::SetTextAligns(TextAlign alignX, TextAlign alignY) {
	this->textAlignX = alignX;
	this->textAlignY = alignY;
}

void DrawableText::SetBodyAligns(TextAlign alignX, TextAlign alignY) {
	this->bodyAlignX = alignX;
	this->bodyAlignY = alignY;
}

void DrawableText::Display() const {
	LVector drawPos(this->body.x, this->body.y);
	drawPos.x += GetAlignedOffset(0.0f, this->body.width / 2, this->body.width, this->bodyAlignX);
	drawPos.y += GetAlignedOffset(0.0f, this->body.height / 2, this->body.height, this->bodyAlignY);

	DrawTextL(this->text, drawPos, this->textSize, this->textAlignX, this->textAlignY, this->textCol);
}

void DrawTextL(const string& text, LVector pos, float size, TextAlign alignX, TextAlign alignY, const LColor& col) {
	LVector textMeasures = MeasureTextEx(GetFontDefault(), text.c_str(), size, (int)(size / 10));
	float lineHeight = textMeasures.y / (std::count(text.begin(), text.end(), '\n') + 1);

	pos.y -= GetAlignedOffset(0.0f, textMeasures.y / 2, textMeasures.y, alignY);

	std::vector<string> lines = str_SplitTokens(text, "\n");

	uint lineIdx = 0;
	for (uint i = 0; i < text.length() && !lines.empty(); i++) {
		if (text[i] == '\n') {
			pos.y += lineHeight;
			continue;
		}

		LVector lineMeasures = MeasureTextEx(GetFontDefault(), lines[lineIdx].c_str(), size, (int)(size / 10));
		LVector linePos = pos;
		linePos.x -= GetAlignedOffset(0.0f, lineMeasures.x / 2, lineMeasures.x, alignX);

		DrawTextEx(GetFontDefault(), lines[lineIdx].c_str(), linePos, size, (int)(size / 10), col);
		pos.y += lineHeight;

		i += lines[lineIdx].length();

		lines.erase(lines.begin());
	}
}
