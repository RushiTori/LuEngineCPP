#include "LRect.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoint.hpp"
#include "LPoly.hpp"
#include "LTriangle.hpp"

void LRect::SetPos(const LVector& pos) {
	this->x = pos.x;
	this->y = pos.y;
}

void LRect::Move(const LVector& vel) {
	this->x += vel.x;
	this->y += vel.y;
}

LVector LRect::GetPos() const { return LVector(this->x, this->y); }

LVector LRect::GetCenter() const { return LVector(this->x + this->w / 2, this->y + this->h / 2); }

Rectangle LRect::GetBoundingBox() const { return *this; }

bool LRect::CheckCollision(const LPoint& other) const { return other.CheckCollision(*this); }

bool LRect::CheckCollision(const LLine& other) const { return other.CheckCollision(*this); }

bool LRect::CheckCollision(const LCircle& other) const { return other.CheckCollision(*this); }

bool LRect::CheckCollision(const LRect& other) const {
	return ((this->x < (other.x + other.w) && other.x < (this->x + this->w)) &&
			(this->y < (other.y + other.h) && other.y < (this->y + this->h)));
}

bool LRect::CheckCollision(const LTriangle& other) const {
	if (other.CheckCollision(LPoint(this->x, this->y))) return true;
	if (other.CheckCollision(LPoint(this->x + this->w, this->y))) return true;
	if (other.CheckCollision(LPoint(this->x + this->w, this->y + this->h))) return true;
	if (other.CheckCollision(LPoint(this->x, this->y + this->h))) return true;

	if (this->CheckCollision(other.pA) || this->CheckCollision(other.pB) || this->CheckCollision(other.pC)) return true;

	if (this->CheckCollision(LLine(other.pA, other.pB))) return true;
	if (this->CheckCollision(LLine(other.pB, other.pC))) return true;
	if (this->CheckCollision(LLine(other.pC, other.pA))) return true;

	return false;
}

bool LRect::CheckCollision(const LPoly& other) const {
	if (other.CheckCollision(LPoint(this->x, this->y))) return true;
	if (other.CheckCollision(LPoint(this->x + this->w, this->y))) return true;
	if (other.CheckCollision(LPoint(this->x + this->w, this->y + this->h))) return true;
	if (other.CheckCollision(LPoint(this->x, this->y + this->h))) return true;

	for (uint i = 0; i < other.points.size(); i++) {
		uint j = (i + 1) % other.points.size();
		if (this->CheckCollision(LLine(other.points[i], other.points[j]))) return true;
		if (this->CheckCollision(other.points[i])) return true;
	}

	return false;
}

void LRect::Display() const { this->skin.DisplayRect(*this, this->col); }

std::ostream& operator<<(std::ostream& os, const LRect& info) {
	os << "{ " << info.x << ", " << info.y << ", " << info.w << ", " << info.h << ", " << info.col << " }";
	return os;
}
