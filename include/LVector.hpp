#ifndef LVECTOR_HPP
#define LVECTOR_HPP

#include <raylib.h>

#include <LuLibCPP/LUtils.hpp>

template <arithmetic T>
struct LuVecBase {
	T x;
	T y;

	LuVecBase() : x(0), y(0) {}
	LuVecBase(T x_, T y_) : x(x_), y(y_) {}
	//LuVecBase(const LuVecBase& other) : x(other.x), y(other.y) {}

	static LuVecBase FromAngle(float angle, float mag = 1.0f) {
		return LuVecBase(std::cos(angle), std::sin(angle)) * mag;
	}

	static LuVecBase Rand(float mag = 1.0f, float startAngle = 0.0f, float endAngle = TWO_PI) {
		int64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::default_random_engine randEngine(seed);
		float randAngle = randEngine() / (float)(randEngine.max());
		return LuVecBase::fromAngle(startAngle + (randAngle * (endAngle - startAngle)), mag);
	}

	operator LuVecBase<float>() const { return LuVecBase<float>(x, y); }
	operator LuVecBase<int32_t>() const { return LuVecBase<int32_t>(std::floor(x), std::floor(y)); }
	operator LuVecBase<uint32_t>() const { return LuVecBase<uint32_t>(std::floor(x), std::floor(y)); }

	// cross lib compatibility
	LuVecBase(const Vector2& other) : x(other.x), y(other.y) {}

	operator Vector2() const { return (Vector2){.x = (float)x, .y = (float)y}; }

	// class method

	static T Dot(const LuVecBase& a, const LuVecBase& b) { return a.x * b.x + a.y * b.y; }

	static T Dist2(const LuVecBase& a, const LuVecBase& b) { return (a - b).Mag2(); }

	static T Dist(const LuVecBase& a, const LuVecBase& b) { return (a - b).Mag(); }

	static LuVecBase Min(const LuVecBase& a, const LuVecBase& b) {
		return LuVecBase(std::min(a.x, b.x), std::min(a.y, b.y));
	}

	static LuVecBase Max(const LuVecBase& a, const LuVecBase& b) {
		return LuVecBase(std::max(a.x, b.x), std::max(a.y, b.y));
	}

	static LuVecBase Clamp(const LuVecBase& vec, const LuVecBase& a, const LuVecBase& b) {
		return LuVecBase(std::clamp(vec.x, a.x, b.x), std::clamp(vec.y, a.y, b.y));
	}

	static float AngleBetween(const LuVecBase& a, const LuVecBase& b) {
		return std::acos(LuVecBase::Dot(a.Norm(), b.Norm()));
	}

	static LuVecBase Lerp(const LuVecBase& a, const LuVecBase& b, float tX, float tY) {
		return LuVecBase(std::lerp(a.x, b.x, tX), std::lerp(a.y, b.y, tY));
	}

	static LuVecBase Lerp(const LuVecBase& a, const LuVecBase& b, float t) { return LuVecBase::Lerp(a, b, t, t); }

	T Dot(const LuVecBase& other) const { return LuVecBase::Dot(*this, other); }

	T Dist2(const LuVecBase& other) const { return LuVecBase::Dist2(*this, other); }

	T Dist(const LuVecBase& other) const { return LuVecBase::Dist(*this, other); }

	LuVecBase Min(const LuVecBase& other) const { return LuVecBase::Min(*this, other); }

	LuVecBase Max(const LuVecBase& other) const { return LuVecBase::Max(*this, other); }

	LuVecBase Clamp(const LuVecBase& a, const LuVecBase& b) const { return LuVecBase::Clamp(*this, a, b); }

	float AngleBetween(const LuVecBase& other) { return LuVecBase::AngleBetween(*this, other); }

	T Mag2() const { return x * x + y * y; }
	T Mag() const { return std::sqrt(Mag2()); }
	T Heading() const { return std::atan2(y, x); }

	LuVecBase Floor() const { return LuVecBase(std::floor(x), std::floor(y)); }
	void ApplyFloor() { *this = this->Floor(); }

	LuVecBase Ceil() const { return LuVecBase(std::ceil(x), std::ceil(y)); }
	void ApplyCeil() { *this = this->Ceil(); }

	LuVecBase Round() const { return LuVecBase(std::round(x), std::round(y)); }
	void ApplyRound() { *this = this->Round(); }

	LuVecBase Norm() const { return *this / this->Mag(); }
	void ApplyNorm() { *this = this->Norm(); }

	LuVecBase Limit(T val) const { return this->Norm() * std::min(this->Mag(), val); }
	void ApplyLimit(T val) { *this = this->Limit(); }

	LuVecBase Map(const LuVecBase& a1, const LuVecBase& b1, const LuVecBase& a2, const LuVecBase& b2) const {
		float tX = proportion(x, a1.x, b1.x);
		float tY = proportion(y, a1.y, b1.y);
		return LuVecBase::Lerp(a2, b2, tX, tY);
	}

	void ApplyMap(const LuVecBase& a1, const LuVecBase& b1, const LuVecBase& a2, const LuVecBase& b2) {
		*this = this->Map(a1, b1, a2, b2);
	}

	LuVecBase ScalarProj(const LuVecBase& a, const LuVecBase& b) const {
		LuVecBase AtoThis(*this - a);
		LuVecBase AtoB(b - a);
		AtoB.ApplyNorm();
		float projMag = LuVecBase::Dot(AtoB, AtoThis);
		return a + AtoB * projMag;
	}

	void ApplyScalarProj(const LuVecBase& a, const LuVecBase& b) { *this = this->ScalarProj(a, b); }

	LuVecBase Rotate(float angle, const LuVecBase& origin = LuVecBase()) const {
		LuVecBase offset(*this - origin);
		return origin + LuVecBase::FromAngle(offset.Heading() + angle, offset.Mag());
	}

	void ApplyRotate(float angle, const LuVecBase& origin = LuVecBase()) { *this = this->Rotate(angle, origin); }

	void SetMag(T val) { *this = this->Norm() * val; }

	// operator overloading

	friend std::ostream& operator<<(std::ostream& os, const LuVecBase& vec) {
		return (os << "{ " << vec.x << ", " << vec.y << " }");
	}

	LuVecBase operator+(const LuVecBase& other) const { return LuVecBase(x + other.x, y + other.y); }

	LuVecBase operator+(T val) const { return LuVecBase(x + val, y + val); }

	LuVecBase& operator+=(const LuVecBase& other) {
		*this = *this + other;
		return *this;
	}

	LuVecBase& operator+=(T val) {
		*this = *this + val;
		return *this;
	}

	LuVecBase operator-() const { return LuVecBase(-x, -y); }

	LuVecBase operator-(const LuVecBase& other) const { return LuVecBase(x - other.x, y - other.y); }

	LuVecBase operator-(T val) const { return LuVecBase(x - val, y - val); }

	LuVecBase& operator-=(const LuVecBase& other) {
		*this = *this - other;
		return *this;
	}

	LuVecBase& operator-=(T val) {
		*this = *this - val;
		return *this;
	}

	LuVecBase operator*(const LuVecBase& other) const { return LuVecBase(x * other.x, y * other.y); }

	LuVecBase operator*(T val) const { return LuVecBase(x * val, y * val); }

	LuVecBase& operator*=(const LuVecBase& other) {
		*this = *this * other;
		return *this;
	}

	LuVecBase& operator*=(T val) {
		*this = *this * val;
		return *this;
	}

	LuVecBase operator/(const LuVecBase& other) const { return LuVecBase(x / other.x, y / other.y); }

	LuVecBase operator/(T val) const { return LuVecBase(x / val, y / val); }

	LuVecBase& operator/=(const LuVecBase& other) {
		*this = *this / other;
		return *this;
	}

	LuVecBase& operator/=(T val) {
		*this = *this / val;
		return *this;
	}

	bool operator==(const LuVecBase& other) { return ((this->x == other.x) && (this->y == other.y)); }

	bool operator!=(const LuVecBase& other) { return !(*this == other); }
};

using LVector = LuVecBase<float>;
using LuVecInt32 = LuVecBase<int32_t>;
using LuVecUInt32 = LuVecBase<uint32_t>;

#endif	// LVECTOR_HPP
