#include "LTriangle.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoint.hpp"
#include "LPoly.hpp"
#include "LRect.hpp"

void LTriangle::SetPos(const LVector& pos) {
	LVector center = (this->pA + this->pB + this->pC) / 3;

	this->pA -= center;
	this->pB -= center;
	this->pC -= center;

	this->pA += pos;
	this->pB += pos;
	this->pC += pos;
}

void LTriangle::Move(const LVector& vel) {
	this->pA += vel;
	this->pB += vel;
	this->pC += vel;
}

LVector LTriangle::GetPos() const { return (this->pA + this->pB + this->pC) / 3; }

LVector LTriangle::GetCenter() const { return (this->pA + this->pB + this->pC) / 3; }

Rectangle LTriangle::GetBoundingBox() const {
	float minX = std::min(this->pA.x, std::min(this->pB.x, this->pC.x));
	float minY = std::min(this->pA.y, std::min(this->pB.y, this->pC.y));

	float maxX = std::max(this->pA.x, std::max(this->pB.x, this->pC.x));
	float maxY = std::max(this->pA.y, std::max(this->pB.y, this->pC.y));

	return (Rectangle){.x = minX, .y = minY, .width = maxX - minX, .height = maxY - minY};
}

bool LTriangle::CheckCollision(const LPoint& other) const { return other.CheckCollision(*this); }

bool LTriangle::CheckCollision(const LLine& other) const { return other.CheckCollision(*this); }

bool LTriangle::CheckCollision(const LCircle& other) const { return other.CheckCollision(*this); }

bool LTriangle::CheckCollision(const LRect& other) const { return other.CheckCollision(*this); }

bool LTriangle::CheckCollision(const LTriangle& other) const {
	if (other.CheckCollision(this->pA) || other.CheckCollision(this->pB) || other.CheckCollision(this->pC)) return true;
	if (this->CheckCollision(other.pA) || this->CheckCollision(other.pB) || this->CheckCollision(other.pC)) return true;

	if (this->CheckCollision(LLine(other.pA, other.pB))) return true;
	if (this->CheckCollision(LLine(other.pB, other.pC))) return true;
	if (this->CheckCollision(LLine(other.pC, other.pA))) return true;

	return false;
}

bool LTriangle::CheckCollision(const LPoly& other) const {
	if (other.CheckCollision(this->pA) || other.CheckCollision(this->pB) || other.CheckCollision(this->pC)) return true;

	for (uint i = 0; i < other.points.size(); i++) {
		uint j = (i + 1) % other.points.size();
		if (this->CheckCollision(LLine(other.points[i], other.points[j]))) return true;
		if (this->CheckCollision(other.points[i])) return true;
	}

	return false;
}

void LTriangle::Display() const { this->skin.DisplayTriangle(this->pA, this->pB, this->pC, this->col); }

std::ostream& operator<<(std::ostream& os, const LTriangle& info) {
	os << "{ " << info.pA << ", " << info.pB << ", " << info.pC << ", " << info.col << " }";
	return os;
}
