#include "LVector.hpp"

LVector LVector::fromAngle(float angle, float mag) { return LVector(std::cos(angle) * mag, std::sin(angle) * mag); }

float LVector::dot(const LVector& vecA, const LVector& vecB) { return vecA.x * vecB.x + vecA.y * vecB.y; }

float LVector::angleBetween(const LVector& vecA, const LVector& vecB) {
	if (vecA.x == 0 && vecA.y == 0) return 0;
	if (vecB.x == 0 && vecB.y == 0) return 0;
	float dot = LVector::dot(vecA, vecB);
	float magA = vecA.mag();
	float magB = vecB.mag();

	float cosAngle = dot / (magA * magB);
	if (cosAngle >= 1) return 0;
	if (cosAngle <= -1) return PI;
	return std::acos(cosAngle);
}

float LVector::dist(const LVector& vecA, const LVector& vecB) {
	LVector temp = vecB - vecA;
	return temp.mag();
}

float LVector::dist2(const LVector& vecA, const LVector& vecB) {
	LVector temp = vecB - vecA;
	return temp.mag2();
}

LVector LVector::lerp(const LVector& start, const LVector& end, float time) {
	return LVector(std::lerp(start.x, end.x, time), std::lerp(start.y, end.y, time));
}

LVector LVector::map(const LVector& val, const LVector& startA, const LVector& endA, const LVector& startB,
					 const LVector& endB) {
	return LVector(mapValue(val.x, startA.x, endA.x, startB.x, endB.x),
				   mapValue(val.y, startA.y, endA.y, startB.y, endB.y));
}

LVector LVector::norm() const { return (*this) / ((mag() == 0) ? 1 : mag()); }

LVector LVector::setMag(float newMag) const { return norm() * newMag; }

LVector LVector::limit(float maxMag) const { return norm() * std::min(mag(), maxMag); }

float LVector::mag() const { return std::sqrt(mag2()); }

float LVector::mag2() const { return x * x + y * y; }

float LVector::heading() const { return std::atan2(y, x); }

LVector LVector::floor() const { return LVector(std::floor(x), std::floor(y)); }

LVector LVector::round() const { return LVector(std::round(x), std::round(y)); }

LVector LVector::ceil() const { return LVector(std::ceil(x), std::ceil(y)); }

LVector LVector::projectOn(const LVector& other) const {
	if (other == LVector()) return LVector();
	float projMag = LVector::dot(*this, other);
	return other * (projMag / other.mag());
}

LVector LVector::clamped(const LVector& vecA, const LVector& vecB) const {
	const float minX = std::min(vecA.x, vecB.x);
	const float maxX = std::max(vecA.x, vecB.x);
	const float minY = std::min(vecA.y, vecB.y);
	const float maxY = std::max(vecA.y, vecB.y);
	return LVector(std::clamp(x, minX, maxX), std::clamp(y, minY, maxY));
}

LVector LVector::rotate(float angle, const LVector& origin) const {
	if (origin == LVector()) {
		if (angle == HALF_PI) {
			return LVector(-y, x);
		} else if (angle == PI) {
			return LVector(-x, -y);
		} else if (angle == PI + HALF_PI) {
			return LVector(y, -x);
		}
		return LVector::fromAngle(heading() + angle, mag());
	}
	LVector toThis = (*this) - origin;
	if (angle == HALF_PI) {
		return origin + LVector(-toThis.y, toThis.x);
	} else if (angle == PI) {
		return origin + LVector(-toThis.x, -toThis.y);
	} else if (angle == PI + HALF_PI) {
		return origin + LVector(toThis.y, -toThis.x);
	}
	return origin + LVector::fromAngle(toThis.heading() + angle, toThis.mag());
}

std::ostream& operator<<(std::ostream& os, const LVector& info) {
	os << "{ " << info.x << ", " << info.y << " }";
	return os;
}

LVector& operator+=(LVector& vec, float scl) {
	vec.x += scl;
	vec.y += scl;
	return vec;
}

LVector operator+(const LVector& vec, float scl) { return LVector(vec.x + scl, vec.y + scl); }

LVector& operator+=(LVector& vec, const LVector& other) {
	vec.x += other.x;
	vec.y += other.y;
	return vec;
}

LVector operator+(const LVector& vec, const LVector& other) { return LVector(vec.x + other.x, vec.y + other.y); }

LVector operator-(const LVector& vec) { return vec * -1; }

LVector& operator-=(LVector& vec, float scl) {
	vec.x -= scl;
	vec.y -= scl;
	return vec;
}

LVector operator-(const LVector& vec, float scl) { return LVector(vec.x - scl, vec.y - scl); }

LVector& operator-=(LVector& vec, const LVector& other) {
	vec.x -= other.x;
	vec.y -= other.y;
	return vec;
}

LVector operator-(const LVector& vec, const LVector& other) { return LVector(vec.x - other.x, vec.y - other.y); }

LVector& operator/=(LVector& vec, float scl) {
	vec.x /= scl;
	vec.y /= scl;
	return vec;
}

LVector operator/(const LVector& vec, float scl) { return LVector(vec.x / scl, vec.y / scl); }

LVector& operator/=(LVector& vec, const LVector& other) {
	vec.x /= other.x;
	vec.y /= other.y;
	return vec;
}

LVector operator/(const LVector& vec, const LVector& other) { return LVector(vec.x / other.x, vec.y / other.y); }

LVector& operator*=(LVector& vec, float scl) {
	vec.x *= scl;
	vec.y *= scl;
	return vec;
}

LVector operator*(const LVector& vec, float scl) { return LVector(vec.x * scl, vec.y * scl); }

LVector& operator*=(LVector& vec, const LVector& other) {
	vec.x *= other.x;
	vec.y *= other.y;
	return vec;
}

LVector operator*(const LVector& vec, const LVector& other) { return LVector(vec.x * other.x, vec.y * other.y); }

bool operator==(const LVector& vec, const LVector& other) {
	return (int(vec.x) == int(other.x)) && (int(vec.y) == int(other.y));
}

bool operator!=(const LVector& vec, const LVector& other) { return !(vec == other); }
