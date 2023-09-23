#include "LCircle.hpp"

#include "LLine.hpp"
#include "LPoint.hpp"
#include "LPoly.hpp"
#include "LRect.hpp"
#include "LTriangle.hpp"

void LCircle::SetPos(const LVector& pos) { this->pos = pos; }

void LCircle::Move(const LVector& vel) { this->pos += vel; }

LVector LCircle::GetPos() const { return this->pos; }

LVector LCircle::GetCenter() const { return this->pos; }

Rectangle LCircle::GetBoundingBox() const {
	return (Rectangle){.x = this->pos.x - r, .y = this->pos.y - r, .width = r * 2, .height = r * 2};
}

bool LCircle::CheckCollision(const LPoint& other) const { return other.CheckCollision(*this); }

bool LCircle::CheckCollision(const LLine& other) const { return other.CheckCollision(*this); }

bool LCircle::CheckCollision(const LCircle& other) const {
	return LVector::dist2(this->pos, other.pos) <= ((this->r + other.r) * (this->r + other.r));
}

bool LCircle::CheckCollision(const LRect& other) const {
	LVector ConRec = this->pos.clamped(LVector(other.x, other.y), LVector(other.x + other.w, other.y + other.h));
	return LVector::dist2(this->pos, ConRec) <= (this->r * this->r);
}

bool LCircle::CheckCollision(const LTriangle& other) const {
	if (other.CheckCollision(this->pos)) return true;

	if (this->CheckCollision(other.pA) || this->CheckCollision(other.pB) || this->CheckCollision(other.pC)) return true;

	if (this->CheckCollision(LLine(other.pA, other.pB))) return true;
	if (this->CheckCollision(LLine(other.pB, other.pC))) return true;
	if (this->CheckCollision(LLine(other.pC, other.pA))) return true;
	return false;
}

bool LCircle::CheckCollision(const LPoly& other) const {
	if (other.CheckCollision(this->pos)) return true;

	for (uint i = 0; i < other.points.size(); i++) {
		uint j = (i + 1) % other.points.size();
		if (this->CheckCollision(LLine(other.points[i], other.points[j]))) return true;
		if (this->CheckCollision(other.points[i])) return true;
	}
	return false;
}

void LCircle::Display() const { this->skin.DisplayCircle(this->pos, this->r, this->col); }

std::ostream& operator<<(std::ostream& os, const LCircle& info) {
	os << "{ " << info.pos << ", " << info.r << ", " << info.col << " }";
	return os;
}
