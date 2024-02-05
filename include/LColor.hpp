#ifndef LCOLOR_HPP
#define LCOLOR_HPP

#include <LuLibCPP/LUtils.hpp>

#include <raylib.h>

struct LColor {
	static constexpr uint32_t R_MASK = 0xFF'00'00'00;
	static constexpr uint32_t R_OFFSET = 8 * 3;

	static constexpr uint32_t G_MASK = 0x00'FF'00'00;
	static constexpr uint32_t G_OFFSET = 8 * 2;

	static constexpr uint32_t B_MASK = 0x00'00'FF'00;
	static constexpr uint32_t B_OFFSET = 8 * 1;

	static constexpr uint32_t A_MASK = 0x00'00'00'FF;
	static constexpr uint32_t A_OFFSET = 8 * 0;

	static const LColor LU_BLACK;

	static const LColor LU_RED;
	static const LColor LU_GREEN;
	static const LColor LU_BLUE;

	static const LColor LU_YELLOW;
	static const LColor LU_CYAN;
	static const LColor LU_MAGENTA;

	static const LColor LU_PINK;
	static const LColor LU_CHARTR;
	static const LColor LU_SKY;
	static const LColor LU_PURPLE;
	static const LColor LU_ORANGE;
	static const LColor LU_TEAL;

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	constexpr LColor() : r(0x00), g(0x00), b(0x00), a(0x00) {}

	constexpr LColor(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 0xFF) : r(r_), g(g_), b(b_), a(a_) {}

	constexpr LColor(uint32_t colCode)
		: r((colCode & LColor::R_MASK) >> LColor::R_OFFSET),
		  g((colCode & LColor::G_MASK) >> LColor::G_OFFSET),
		  b((colCode & LColor::B_MASK) >> LColor::B_OFFSET),
		  a((colCode & LColor::A_MASK) >> LColor::A_OFFSET) {}

	constexpr operator uint32_t() const {
		return ((uint32_t)(r) << LColor::R_OFFSET) | ((uint32_t)(g) << LColor::G_OFFSET) |
			   ((uint32_t)(b) << LColor::B_OFFSET) | ((uint32_t)(a) << LColor::A_OFFSET);
	}

	// cross lib compatibility

	constexpr LColor(const Color& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

	constexpr operator Color() const {
		return (Color){
			.r = r,
			.g = g,
			.b = b,
			.a = a,
		};
	}

	// class method

	// inputs must be in range 0-1 inclusive
	static LColor FromHSB(float hue, float sat, float bri, uint8_t a = 0xFF) {
		// WIP
		if (hue < 0) {
			hue = 0 + (hue - std::floor(hue));
		} else {
			hue -= std::floor(hue);
		}
		sat = std::clamp(sat, 0.0f, 1.0f);
		bri = std::clamp(bri, 0.0f, 1.0f);
		if (sat == 0) return LColor(bri * 0xFF, bri * 0xFF, bri * 0xFF, a);

		int i = std::floor(6 * hue);
		float f = 6 * hue - i;
		float p = 0xFF * (bri * (1 - sat));
		float q = 0xFF * (bri * (1 - sat * f));
		float t = 0xFF * (bri * (1 - sat * (1 - f)));
		bri *= 0xFF;

		switch (i) {
			case 0:
				return LColor(bri, t, p, a);
			case 1:
				return LColor(q, bri, p, a);
			case 2:
				return LColor(p, bri, t, a);
			case 3:
				return LColor(p, q, bri, a);
			case 4:
				return LColor(t, p, bri, a);
			case 5:
				return LColor(bri, p, q, a);
			default:
				break;
		}
		return LColor();
	}

	static LColor RandRGB(uint8_t a = 0xFF) {
		int64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::default_random_engine randEngine(seed);
		return LColor(randEngine(), randEngine(), randEngine(), a);
	}

	static LColor RandHSB(uint8_t a = 0xFF) {
		int64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::default_random_engine randEngine(seed);
		float randHue = randEngine() / (float)std::default_random_engine::max();
		float randSat = randEngine() / (float)std::default_random_engine::max();
		float randBri = randEngine() / (float)std::default_random_engine::max();
		return LColor::FromHSB(randHue, randSat, randBri, a);
	}

	static LColor Lerp(const LColor& a, const LColor& b, float tR, float tG, float tB, float tA) {
		return LColor(std::lerp(a.r, b.r, tR), std::lerp(a.g, b.g, tG), std::lerp(a.b, b.b, tB),
					  std::lerp(a.a, b.a, tA));
	}

	static LColor Lerp(const LColor& a, const LColor& b, float t) { return LColor::Lerp(a, b, t, t, t, t); }

	LColor Fade(uint8_t a_) const { return LColor(r, g, b, a_); }
	void ApplyFade(uint8_t a_) { a = a_; }

	// operator overloading

	friend std::ostream& operator<<(std::ostream& os, const LColor& col) {
		return (os << "{ " << (uint32_t)col.r << ", " << (uint32_t)col.g << ", " << (uint32_t)col.b << ", "
				   << (uint32_t)col.a << " }");
	}

	LColor operator+(const LColor& other) const { return LColor(r + other.r, g + other.g, b + other.b, a + other.a); }

	LColor& operator+=(const LColor& other) {
		*this = *this + other;
		return *this;
	}

	LColor operator-(const LColor& other) const { return LColor(r - other.r, g - other.g, b - other.b, a - other.a); }

	LColor& operator-=(const LColor& other) {
		*this = *this - other;
		return *this;
	}

	LColor operator*(const LColor& other) const { return LColor(r * other.r, g * other.g, b * other.b, a * other.a); }

	LColor& operator*=(const LColor& other) {
		*this = *this * other;
		return *this;
	}

	LColor operator/(const LColor& other) const { return LColor(r / other.r, g / other.g, b / other.b, a / other.a); }

	LColor& operator/=(const LColor& other) {
		*this = *this / other;
		return *this;
	}

	bool operator==(const LColor& other) const {
		return ((r == other.r) && (g == other.g) && (b == other.b) && (a == other.a));
	}

	bool operator!=(const LColor& other) const { return !(*this == other); }
};

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

#endif	// LCOLOR_HPP
