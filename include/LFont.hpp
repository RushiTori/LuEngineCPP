#ifndef LFONT_HPP
#define LFONT_HPP

#include "LAligns.hpp"
#include "SpriteSheet.hpp"

class LFont {
   private:
	SpriteSheet sheet;

   public:
	void Load(const std::string& fontPath, uint32_t glyphW, uint32_t glyphH);
	void Unload();

	void Display(const std::string& text, const LVector& pos, LAligns::type alignX = LAligns::LEFT,
				 LAligns::type alignY = LAligns::TOP) const;

	void Display(const std::string& text, const LVector& pos, float scaleX, float scaleY,
				 LAligns::type alignX = LAligns::LEFT, LAligns::type alignY = LAligns::TOP) const;

	void Display(const std::string& text, const LVector& pos, const LVector& scales,
				 LAligns::type alignX = LAligns::LEFT, LAligns::type alignY = LAligns::TOP) const;

	void Display(const std::string& text, const LVector& pos, float rotation, LAligns::type alignX = LAligns::LEFT,
				 LAligns::type alignY = LAligns::TOP) const;

	void Display(const std::string& text, const LVector& pos, float rotation, float scaleX, float scaleY,
				 LAligns::type alignX = LAligns::LEFT, LAligns::type alignY = LAligns::TOP) const;

	void Display(const std::string& text, const LVector& pos, float rotation, const LVector& scales,
				 LAligns::type alignX = LAligns::LEFT, LAligns::type alignY = LAligns::TOP) const;

	LVector MeasureGlyph(char glyph) const;
	LVector MeasureText(const std::string& text) const;

   public:
	static std::string FormatColor(const LColor& col);
	static uint32_t CheckColorFormat(const std::string& colCode);
	static LColor ParseColor(const std::string& formatted);
};

#endif	// LFONT_HPP

// caution     : any invalid format will be shown as plain text !!!

// color char  : \x01
// alpha channel defaults to 255(dec) if not otherwise specified
// color specs : [#RRGGBBAA] (in hex)
// \n will be a new line
// \t will be 4 spaces
