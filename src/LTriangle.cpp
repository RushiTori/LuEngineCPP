#include "LTriangle.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoint.hpp"
#include "LPoly.hpp"
#include "LRect.hpp"

void LTriangle::SetCenter(const LVector& pos) {
	LVector center = GetCenter();

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

LVector LTriangle::GetCenter() const { return (this->pA + this->pB + this->pC) / 3; }

Rectangle LTriangle::GetBoundingBox() const {
	float minX = std::min(this->pA.x, std::min(this->pB.x, this->pC.x));
	float minY = std::min(this->pA.y, std::min(this->pB.y, this->pC.y));

	float maxX = std::max(this->pA.x, std::max(this->pB.x, this->pC.x));
	float maxY = std::max(this->pA.y, std::max(this->pB.y, this->pC.y));

	return (Rectangle){.x = minX, .y = minY, .width = maxX - minX, .height = maxY - minY};
}

uint LTriangle::GetPointsCount() const { return 3; }

LVector LTriangle::GetPoint(uint idx) const {
	if (idx == 0) return this->pA;
	if (idx == 1) return this->pB;
	if (idx == 2) return this->pC;
	return LVector();
}

std::vector<LVector> LTriangle::GetPoints() const { return {this->pA, this->pB, this->pC}; }

void LTriangle::Display() const { this->skin.DisplayTriangle(this->pA, this->pB, this->pC, this->col); }

std::ostream& operator<<(std::ostream& os, const LTriangle& info) {
	os << "{ " << info.pA << ", " << info.pB << ", " << info.pC << ", " << info.col << " }";
	return os;
}
