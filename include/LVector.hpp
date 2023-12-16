#ifndef LVECTOR_HPP
#define LVECTOR_HPP

#include <rayconfig.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#ifndef LU_CONSTANTS_HPP
#undef PI
#endif	// LU_CONSTANTS_HPP

#include <LuLibCPP/LuUtils.hpp>

struct LVector {
	float x, y;

	// All the constructors and static functions
	LVector(float x_ = 0, float y_ = 0) : x(x_), y(y_) {}

	LVector(const LVector& other) = default;

	static LVector fromAngle(float angle, float mag = 1.0f);
	static LVector rand(float mag = 1.0f, float startAngle = 0.0f, float endAngle = TWO_PI);
	static float dot(const LVector& vecA, const LVector& vecB);
	static float angleBetween(const LVector& vecA, const LVector& vecB);
	static float dist(const LVector& vecA, const LVector& vecB);
	static float dist2(const LVector& vecA, const LVector& vecB);
	static LVector lerp(const LVector& start, const LVector& end, float time);
	static LVector map(const LVector& val, const LVector& startA, const LVector& endA, const LVector& startB,
					   const LVector& endB);

	// To make it compatible with other libs
	LVector(const Vector2& other) : x(other.x), y(other.y) {}

	operator Vector2() const { return (Vector2){.x = x, .y = y}; }

	// Regular functions
	LVector norm() const;
	LVector setMag(float newMag) const;
	LVector limit(float maxMag) const;

	float mag() const;
	float mag2() const;
	float heading() const;

	LVector floor() const;
	LVector round() const;
	LVector ceil() const;

	LVector projectOn(const LVector& other) const;
	LVector projectOn(const LVector& vecA, const LVector& vecB) const;
	int side(const LVector& other) const;
	int side(const LVector& vecA, const LVector& vecB) const;
	LVector clamped(const LVector& vecA, const LVector& vecB) const;
	LVector rotate(float angle, const LVector& origin = LVector()) const;
};

std::ostream& operator<<(std::ostream& os, const LVector& info);

LVector& operator+=(LVector& vec, float scl);
LVector operator+(const LVector& vec, float scl);

LVector& operator+=(LVector& vec, const LVector& other);
LVector operator+(const LVector& vec, const LVector& other);

LVector operator-(const LVector& vec);

LVector& operator-=(LVector& vec, float scl);
LVector operator-(const LVector& vec, float scl);

LVector& operator-=(LVector& vec, const LVector& other);
LVector operator-(const LVector& vec, const LVector& other);

LVector& operator/=(LVector& vec, float scl);
LVector operator/(const LVector& vec, float scl);

LVector& operator/=(LVector& vec, const LVector& other);
LVector operator/(const LVector& vec, const LVector& other);

LVector& operator*=(LVector& vec, float scl);
LVector operator*(const LVector& vec, float scl);

LVector& operator*=(LVector& vec, const LVector& other);
LVector operator*(const LVector& vec, const LVector& other);

bool operator==(const LVector& vec, const LVector& other);
bool operator!=(const LVector& vec, const LVector& other);

#endif	// LVECTOR_HPP
