#include "LLine.hpp"

uint LLine::GetPointsCount() const { return 2; }

LVector LLine::GetPoint(uint idx) const {
	if (idx == 0) return this->pA;
	if (idx == 1) return this->pB;
	return LVector();
}

bool LLine::CheckCollision(const LVector& point) const {
	float distA = LVector::dist(this->pA, point);
	float distB = LVector::dist(this->pB, point);

	float distAB = distA + distB;

	float realDist = LVector::dist(this->pA, this->pB);

	return ((distAB >= realDist - 0.05f) && (distAB <= realDist + 0.05f));
}

bool LLine::CheckCollision(const LVector& lineStart, const LVector& lineEnd) const {
	float lineDistY = lineEnd.y - lineStart.y;
	float lineDistX = lineEnd.x - lineStart.x;

	float denom = (lineDistY * (this->pB.x - this->pA.x)) - (lineDistX * (this->pB.y - this->pA.y));

	float uA = (lineDistX * (this->pA.y - lineStart.y) - lineDistY * (this->pA.x - lineStart.x)) / denom;
	float uB = ((this->pB.x - this->pA.x) * (this->pA.y - lineStart.y) -
				(this->pB.y - this->pA.y) * (this->pA.x - lineStart.x)) /
			   denom;

	return ((uA > 0 && uA < 1) && (uB > 0 && uB < 1));
}

bool LLine::CheckCollision(const LVector& center, float radius) const {
	if (LVector::dist2(this->pA, center) <= (radius * radius)) return true;
	if (LVector::dist2(this->pB, center) <= (radius * radius)) return true;

	LVector AtoB = this->pB - this->pA;
	LVector AtoCenter = center - this->pA;

	float dotScale = LVector::dot(AtoCenter, AtoB.norm());
	if ((dotScale < 0) || ((dotScale * dotScale) > AtoB.mag2())) return false;

	LVector ConAB = this->pA + AtoB.setMag(dotScale);

	return (LVector::dist2(ConAB, center) <= (radius * radius));
}

bool LLine::CheckCollision(const LShape& shape) const { return shape.CheckCollision(this->pA, this->pB); }

void LLine::Display() const { DrawLineEx(this->pA, this->pB, 2, this->col); }

void LLine::ResetPoints(const std::vector<LVector>& points) {
	this->pA = points[0];
	this->pB = points[1];
}

std::ostream& operator<<(std::ostream& os, const LLine& info) {
	os << "{ " << info.pA << ", " << info.pB << ", " << info.col << " }";
	return os;
}
