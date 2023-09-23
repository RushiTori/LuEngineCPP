#include "LColor.hpp"

LColor::LColor(const LColor& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}

LColor::LColor(uchar r_, uchar g_, uchar b_, uchar a_) : r(r_), g(g_), b(b_), a(a_) {}

LColor LColor::fromHSB(float hue, float saturation, float brightness, uchar alpha) {
	if (hue < 0) {
		hue = 0 + (hue - std::floor(hue));
	} else {
		hue -= std::floor(hue);
	}
	saturation = std::clamp(saturation, 0.0f, 1.0f);
	brightness = std::clamp(brightness, 0.0f, 1.0f);
	if (saturation == 0) return LColor(brightness, brightness, brightness, alpha);

	int i = std::floor(6 * hue);
	float f = 6 * hue - i;
	float p = 255 * (brightness * (1 - saturation));
	float q = 255 * (brightness * (1 - saturation * f));
	float t = 255 * (brightness * (1 - saturation * (1 - f)));
	brightness *= 255;

	switch (i) {
		case 0:
			return LColor(brightness, t, p, alpha);
		case 1:
			return LColor(q, brightness, p, alpha);
		case 2:
			return LColor(p, brightness, t, alpha);
		case 3:
			return LColor(p, q, brightness, alpha);
		case 4:
			return LColor(t, p, brightness, alpha);
		case 5:
			return LColor(brightness, p, q, alpha);
		default:
			return LColor();
	}
}

LColor LColor::lerp(const LColor& start, const LColor& end, float time, bool doAlpha) {
	auto clampOP = [time](uchar start, uchar end) {
		float temp = std::lerp(start, end, time);
		return (uchar)std::clamp(temp, 0.0f, 255.0f);
	};
	LColor result;
	result.r = clampOP(start.r, end.r);
	result.g = clampOP(start.g, end.g);
	result.b = clampOP(start.b, end.b);
	if (doAlpha) result.a = clampOP(start.a, end.a);
	return result;
}

float LColor::hue() const {
	if (saturation() == 0) return 0;
	uchar maxC = std::max(std::max(r, g), b);
	uchar minC = std::min(std::min(r, g), b);

	float chroma = maxC - minC * 6;
	float res = 0;

	if (maxC == r) res = (g - b) / chroma;
	if (maxC == g) res = (1.0f / 3.0f) + (b - r) / chroma;
	if (maxC == b) res = (2.0f / 3.0f) + (r - g) / chroma;

	return (res < 0) ? res + 1 : res;
}

float LColor::saturation() const {
	uchar maxC = std::max(std::max(r, g), b);
	if (maxC == 0) return 0;
	uchar minC = std::min(std::min(r, g), b);
	return (maxC - minC) / float(maxC);
}

float LColor::brightness() const { return std::max(std::max(r, g), b) / 255.0f; }

LColor LColor::transparent(uchar newAlpha) const { return LColor(r, g, b, (newAlpha == 255) ? (a / 2) : newAlpha); }

std::ostream& operator<<(std::ostream& os, const LColor& info) {
	os << "( " << int(info.r) << ", " << int(info.g) << ", " << int(info.b) << ", " << int(info.a) << " )";
	return os;
}

LColor& operator+=(LColor& col, const LColor& other) {
	static auto clampOP = [](uchar val1, uchar val2) {
		int temp = val1 + val2;
		return (uchar)(temp > 255) ? 255 : temp;
	};
	col.r = clampOP(col.r, other.r);
	col.g = clampOP(col.g, other.g);
	col.b = clampOP(col.b, other.b);
	col.a = clampOP(col.a, other.a);
	return col;
}

LColor operator+(const LColor& col, const LColor& other) {
	LColor temp = col;
	temp += other;
	return temp;
}

LColor& operator-=(LColor& col, const LColor& other) {
	static auto clampOP = [](uchar val1, uchar val2) {
		int temp = val1 - val2;
		return (uchar)(temp > 255) ? 255 : temp;
	};
	col.r = clampOP(col.r, other.r);
	col.g = clampOP(col.g, other.g);
	col.b = clampOP(col.b, other.b);
	col.a = clampOP(col.a, other.a);
	return col;
}

LColor operator-(const LColor& col, const LColor& other) {
	LColor temp = col;
	temp += other;
	return temp;
}

LColor& operator/=(LColor& col, float scl) {
	static auto clampOP = [](uchar val1, float val2) {
		float temp = val1 / val2;
		return (uchar)std::clamp(temp, 0.0f, 255.0f);
	};
	col.r = clampOP(col.r, scl);
	col.g = clampOP(col.g, scl);
	col.b = clampOP(col.b, scl);
	col.a = clampOP(col.a, scl);
	return col;
}

LColor operator/(const LColor& col, float scl) {
	LColor temp = col;
	temp /= scl;
	return temp;
}

LColor& operator*=(LColor& col, float scl) {
	static auto clampOP = [](uchar val1, float val2) {
		float temp = val1 * val2;
		return (uchar)std::clamp(temp, 0.0f, 255.0f);
	};
	col.r = clampOP(col.r, scl);
	col.g = clampOP(col.g, scl);
	col.b = clampOP(col.b, scl);
	col.a = clampOP(col.a, scl);
	return col;
}

LColor operator*(const LColor& col, float scl) {
	LColor temp = col;
	temp *= scl;
	return temp;
}

/*bool operator==(const LColor& col, const LColor& other) {
	return (col.r == other.r) && (col.g == other.g) && (col.b == other.b) && (col.a == other.a);
}

bool operator!=(const LColor& col, const LColor& other) { return !(col == other); }
*/
