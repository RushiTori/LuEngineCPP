#ifndef LCOLOR_HPP
#define LCOLOR_HPP

#include <rayconfig.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <LuLibCPP/LuUtils.hpp>

#undef YELLOW
#undef RED
#undef GREEN
#undef BLUE
#undef WHITE
#undef BLACK
#undef BLANK
#undef MAGENTA

struct LColor {
	static const uint RED_OFFSET, GREEN_OFFSET, BLUE_OFFSET, ALPHA_OFFSET;
	static const uint RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK;

	static const LColor BLANK;
	static const LColor BLACK, DARK_GREY, GREY, LIGHT_GREY, WHITE;
	static const LColor RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW;
	static const LColor LU_BLACK, LU_RED, LU_GREEN, LU_BLUE, LU_CYAN, LU_MAGENTA, LU_YELLOW;
	static const LColor LU_PINK, LU_CHARTR, LU_SKY, LU_PURPLE, LU_ORANGE, LU_TEAL;

	static const std::vector<LColor> greyscaleColors, basicColors, luColors, allColors;

	uchar r, g, b, a;
	// All the constructors and static functions
	LColor(uchar r_ = 0, uchar g_ = 0, uchar b_ = 0, uchar a_ = 255) : r(r_), g(g_), b(b_), a(a_) {}

	LColor(const LColor& other) = default;

	static LColor fromHSB(float hue, float saturation, float brightness, uchar alpha = 255);
	static LColor lerp(const LColor& start, const LColor& end, float time, bool doAlpha = false);

	LColor(uint colCode)
		: r((colCode & RED_MASK) >> RED_OFFSET),
		  g((colCode & GREEN_MASK) >> GREEN_OFFSET),
		  b((colCode & BLUE_MASK) >> BLUE_OFFSET),
		  a((colCode & ALPHA_MASK) >> ALPHA_OFFSET) {}

	operator uint() { return uint(r << 24) | (g << 16) | (b << 8) | a; }

	// To make it compatible with other libs
	LColor(const Color& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

	operator Color() const { return (Color){.r = r, .g = g, .b = b, .a = a}; }

	// Regular functions
	float hue() const;
	float saturation() const;
	float brightness() const;
	LColor transparent(uchar newAlpha = 255) const;
};

inline const uint LColor::RED_MASK = 0xff000000;
inline const uint LColor::RED_OFFSET = 24;
inline const uint LColor::GREEN_MASK = 0x00ff0000;
inline const uint LColor::GREEN_OFFSET = 16;
inline const uint LColor::BLUE_MASK = 0x0000ff00;
inline const uint LColor::BLUE_OFFSET = 8;
inline const uint LColor::ALPHA_MASK = 0x000000ff;
inline const uint LColor::ALPHA_OFFSET = 0;

inline const LColor LColor::BLANK = LColor(0x00, 0x00, 0x00, 0x00);

inline const LColor LColor::BLACK = LColor(0x00, 0x00, 0x00, 0xFF);
inline const LColor LColor::DARK_GREY = LColor(0x4B, 0x4B, 0x4B, 0xFF);
inline const LColor LColor::GREY = LColor(0x96, 0x96, 0x96, 0xFF);
inline const LColor LColor::LIGHT_GREY = LColor(0xC8, 0xC8, 0xC8, 0xFF);
inline const LColor LColor::WHITE = LColor(0xFF, 0xFF, 0xFF, 0xFF);

inline const LColor LColor::RED = LColor(0xFF, 0x00, 0x00, 0xFF);
inline const LColor LColor::GREEN = LColor(0x00, 0xFF, 0x00, 0xFF);
inline const LColor LColor::BLUE = LColor(0x00, 0x00, 0xFF, 0xFF);
inline const LColor LColor::CYAN = LColor(0x00, 0xFF, 0xFF, 0xFF);
inline const LColor LColor::MAGENTA = LColor(0xFF, 0x00, 0xFF, 0xFF);
inline const LColor LColor::YELLOW = LColor(0xFF, 0xFF, 0x00, 0xFF);

inline const LColor LColor::LU_BLACK = LColor(0x32, 0x32, 0x32, 0xFF);
inline const LColor LColor::LU_RED = LColor(0xFF, 0x32, 0x32, 0xFF);
inline const LColor LColor::LU_GREEN = LColor(0x32, 0xFF, 0x32, 0xFF);
inline const LColor LColor::LU_BLUE = LColor(0x32, 0x32, 0xFF, 0xFF);
inline const LColor LColor::LU_CYAN = LColor(0x32, 0xFF, 0xFF, 0xFF);
inline const LColor LColor::LU_MAGENTA = LColor(0xFF, 0x32, 0xFF, 0xFF);
inline const LColor LColor::LU_YELLOW = LColor(0xFF, 0xFF, 0x32, 0xFF);

inline const LColor LColor::LU_PINK = LColor(0xFF, 0xAF, 0xE1, 0xFF);
inline const LColor LColor::LU_CHARTR = LColor(0xE1, 0xFF, 0xAF, 0xFF);
inline const LColor LColor::LU_SKY = LColor(0xAF, 0xE1, 0xFF, 0xFF);
inline const LColor LColor::LU_PURPLE = LColor(0xE1, 0xAF, 0xFF, 0xFF);
inline const LColor LColor::LU_ORANGE = LColor(0xFF, 0xE1, 0xAF, 0xFF);
inline const LColor LColor::LU_TEAL = LColor(0xAF, 0xFF, 0xE1, 0xFF);

inline const std::vector<LColor> LColor::greyscaleColors = {BLACK, DARK_GREY, GREY, LIGHT_GREY, WHITE};

inline const std::vector<LColor> LColor::basicColors = {RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW};

inline const std::vector<LColor> LColor::luColors = {LU_BLACK,	 LU_RED,	LU_GREEN, LU_BLUE,	 LU_CYAN,
													 LU_MAGENTA, LU_YELLOW, LU_PINK,  LU_CHARTR, LU_SKY,
													 LU_PURPLE,	 LU_ORANGE, LU_TEAL};

inline const std::vector<LColor> LColor::allColors = {BLACK,   DARK_GREY, GREY,	   LIGHT_GREY, WHITE,	   RED,
													  GREEN,   BLUE,	  CYAN,	   MAGENTA,	   YELLOW,	   LU_BLACK,
													  LU_RED,  LU_GREEN,  LU_BLUE, LU_CYAN,	   LU_MAGENTA, LU_YELLOW,
													  LU_PINK, LU_CHARTR, LU_SKY,  LU_PURPLE,  LU_ORANGE,  LU_TEAL};

std::ostream& operator<<(std::ostream& os, const LColor& info);

LColor& operator+=(LColor& col, const LColor& other);
LColor operator+(const LColor& col, const LColor& other);
LColor& operator-=(LColor& col, const LColor& other);
LColor operator-(const LColor& col, const LColor& other);
LColor& operator/=(LColor& col, float scl);
LColor operator/(const LColor& col, float scl);
LColor& operator*=(LColor& col, float scl);
LColor operator*(const LColor& col, float scl);

bool operator==(const LColor& col, const LColor& other);
bool operator != (const LColor& col, const LColor& other);

#endif	// LCOLOR_HPP
