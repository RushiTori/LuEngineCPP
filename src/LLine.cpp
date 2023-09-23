#include "LLine.hpp"

#include "LCircle.hpp"
#include "LPoint.hpp"
#include "LPoly.hpp"
#include "LRect.hpp"
#include "LTriangle.hpp"

void LLine::SetPos(const LVector& pos) {
	LVector center = (this->pA + this->pB) / 2;

	this->pA -= center;
	this->pB -= center;

	this->pA += pos;
	this->pB += pos;
}

void LLine::Move(const LVector& vel) {
	LVector center = (this->pA + this->pB) / 2;

	this->pA -= center;
	this->pB -= center;

	center += vel;

	this->pA += center;
	this->pB += center;
}

LVector LLine::GetPos() const { return (this->pA + this->pB) / 2; }

LVector LLine::GetCenter() const { return (this->pA + this->pB) / 2; }

Rectangle LLine::GetBoundingBox() const {
	return (Rectangle){.x = std::min(this->pA.x, this->pB.x),
					   .y = std::min(this->pA.y, this->pB.y),
					   .width = std::max(this->pA.x, this->pB.x) - std::min(this->pA.x, this->pB.x),
					   .height = std::max(this->pA.y, this->pB.y) - std::min(this->pA.y, this->pB.y)};
}

bool LLine::CheckCollision(const LPoint& other) const { return other.CheckCollision(*this); }

bool LLine::CheckCollision(const LLine& other) const {
	float denom = ((other.pB.y - other.pA.y) * (this->pB.x - this->pA.x)) -
				  ((other.pB.x - other.pA.x) * (this->pB.y - this->pA.y));

	float uA = ((other.pB.x - other.pA.x) * (this->pA.y - other.pA.y) -
				(other.pB.y - other.pA.y) * (this->pA.x - other.pA.x)) /
			   denom;

	float uB = ((this->pB.x - this->pA.x) * (this->pA.y - other.pA.y) -
				(this->pB.y - this->pA.y) * (this->pA.x - other.pA.x)) /
			   denom;

	return ((uA > 0 && uA < 1) && (uB > 0 && uB < 1));
}

bool LLine::CheckCollision(const LCircle& other) const {
	if (other.CheckCollision(this->pA) || other.CheckCollision(this->pB)) return true;

	LVector AB = this->pB - this->pA;
	float ConABmag = LVector::dot(AB.norm(), other.pos);

	if ((ConABmag < 0) || ((ConABmag * ConABmag) > AB.mag2())) return false;

	LVector ConAB = AB.setMag(ConABmag);
	return other.CheckCollision(ConAB);
}

bool LLine::CheckCollision(const LRect& other) const {
	if (other.CheckCollision(this->pA) || other.CheckCollision(this->pB)) return true;
	if (this->CheckCollision(LLine(other.x, other.y, other.x + other.w, other.y))) return true;
	if (this->CheckCollision(LLine(other.x + other.w, other.y, other.x + other.w, other.y + other.h))) return true;
	if (this->CheckCollision(LLine(other.x + other.w, other.y + other.h, other.x, other.y + other.h))) return true;
	if (this->CheckCollision(LLine(other.x, other.y + other.h, other.x, other.y))) return true;
	return false;
}

bool LLine::CheckCollision(const LTriangle& other) const {
	if (other.CheckCollision(this->pA) || other.CheckCollision(this->pB)) return true;
	if (this->CheckCollision(LLine(other.pA, other.pB))) return true;
	if (this->CheckCollision(LLine(other.pB, other.pC))) return true;
	if (this->CheckCollision(LLine(other.pC, other.pA))) return true;
	return false;
}

bool LLine::CheckCollision(const LPoly& other) const {
	if (other.CheckCollision(this->pA) || other.CheckCollision(this->pB)) return true;
	for (uint i = 0; i < other.points.size(); i++) {
		uint j = (i + 1) % other.points.size();
		if (this->CheckCollision(LLine(other.points[i], other.points[j]))) return true;
	}
	return false;
}

void LLine::Display() const { this->skin.DisplayTriangle(this->pA, this->pB, this->pB, this->col); }

std::ostream& operator<<(std::ostream& os, const LLine& info) {
	os << "{ " << info.pA << ", " << info.pB << ", " << info.col << " }";
	return os;
}
