#include "LFont.hpp"

void LFont::Load(const std::string& fontPath, uint32_t glyphW, uint32_t glyphH) {
	sheet.Load(fontPath, glyphW, glyphH);
}

void LFont::Unload() { sheet.Unload(); }

void LFont::Display(const std::string& text, const LVector& pos, LAligns::type alignX, LAligns::type alignY) const {
	Display(text, pos, 0, LVector(1, 1), alignX, alignY);
}

void LFont::Display(const std::string& text, const LVector& pos, float scaleX, float scaleY, LAligns::type alignX,
					LAligns::type alignY) const {
	Display(text, pos, 0, LVector(scaleX, scaleY), alignX, alignY);
}

void LFont::Display(const std::string& text, const LVector& pos, const LVector& scales, LAligns::type alignX,
					LAligns::type alignY) const {
	Display(text, pos, 0, scales, alignX, alignY);
}

void LFont::Display(const std::string& text, const LVector& pos, float rotation, LAligns::type alignX,
					LAligns::type alignY) const {
	Display(text, pos, rotation, LVector(1, 1), alignX, alignY);
}

void LFont::Display(const std::string& text, const LVector& pos, float rotation, float scaleX, float scaleY,
					LAligns::type alignX, LAligns::type alignY) const {
	Display(text, pos, rotation, LVector(scaleX, scaleY), alignX, alignY);
}

void LFont::Display(const std::string& text, const LVector& pos, float rotation, const LVector& scales,
					LAligns::type alignX, LAligns::type alignY) const {
	LVector textSizes = LFont::MeasureText(text) * scales;
	LVector textAlignedOffset = LAligns::AlignedOffset(textSizes, alignX, alignY);

	LVector lineSizes = LFont::MeasureText(text.substr(0, text.find_first_of('\n'))) * scales;

	LVector currOffset;
	currOffset.x = LAligns::AlignedOffset(lineSizes, alignX, alignY).x;
	LColor currTint(WHITE);

	float glyphW = 32 * scales.x;
	float glyphH = 32 * scales.y;

	for (uint32_t i = 0; i < text.length(); i++) {
		if (text.at(i) > '\0' && text.at(i) < ' ') {
			// Do the escape chars effects
			if (text.at(i) == '\x01' && i < text.length() - 1) {
				std::string colCode = text.substr(i + 1);
				uint32_t codeLen = LFont::CheckColorFormat(colCode);
				if (codeLen) {
					currTint = LFont::ParseColor(colCode.substr(2));
					i += codeLen;
				}
			} else if (text.at(i) == '\t') {
				currOffset.x += glyphW * 4;
			} else if (text.at(i) == '\n') {
				lineSizes = LFont::MeasureText(text.substr(i + 1, (text).find_first_of('\n', i + 1) - i - 1)) * scales;
				currOffset.x = LAligns::AlignedOffset(lineSizes, alignX, alignY).x;
				currOffset.y += glyphH;
			}
		} else {
			uint8_t glyphIdx = (uint8_t)text.at(i) - ' ';

			LVector glyphOffset = currOffset;
			glyphOffset.y += textAlignedOffset.y;

			sheet.GetTexView(glyphIdx).Display(pos + glyphOffset.Rotate(rotation), rotation, scales, LVector(),
											   currTint);
			currOffset.x += glyphW;
		}
	}
}

LVector LFont::MeasureGlyph(char glyph) const { return LVector(32, 32) * (glyph < '\0' || glyph >= ' '); }

LVector LFont::MeasureText(const std::string& text) const {
	if (text.empty()) return LVector();
	LVector textSizes;
	float lineX = 0;
	for (uint32_t i = 0; i < text.length(); i++) {
		if (text.at(i) == '\x01' && i < text.length() - 1) {
			std::string colCode = text.substr(i + 1);
			uint32_t codeLen = LFont::CheckColorFormat(colCode);
			i += codeLen;
		} else if (text.at(i) == '\n') {
			textSizes.x = std::max(textSizes.x, lineX);
			textSizes.y += 32;
			lineX = 0;
		} else if (text.at(i) == '\t') {
			lineX += LFont::MeasureGlyph(' ').x * 4;
		} else {
			lineX += LFont::MeasureGlyph(text.at(i)).x;
		}
	}
	textSizes.x = std::max(textSizes.x, lineX);
	textSizes.y += 32;
	return textSizes;
}

std::string LFont::FormatColor(const LColor& col) {
	std::stringstream colFormat;
	colFormat << "\01[#";
	colFormat << std::setfill('0') << std::setw(8) << std::hex << (uint32_t)col;
	colFormat << "]";
	return colFormat.str();
}

uint32_t LFont::CheckColorFormat(const std::string& colCode) {
	if (colCode.at(0) != '[') return 0;
	uint32_t end = colCode.find_first_of(']');
	if (end >= colCode.length()) return 0;
	uint32_t codeLen = end - 1;
	if (codeLen != 9) return 0;
	if (colCode.at(1) != '#') return 0;
	uint32_t err = 2 + (colCode.substr(2)).find_first_not_of("0123456789abcdefABCDEF");
	if (err < codeLen) return 0;
	return codeLen + 2;
}

LColor LFont::ParseColor(const std::string& formatted) { return LColor((uint32_t)std::stoul(formatted, nullptr, 16)); }
