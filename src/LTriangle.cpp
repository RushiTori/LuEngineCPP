#include "LTriangle.hpp"

uint LTriangle::GetPointsCount() const { return 3; }

LVector LTriangle::GetPoint(uint idx) const {
	if (idx == 0) return this->pA;
	if (idx == 1) return this->pB;
	if (idx == 2) return this->pC;
	return LVector();
}

void LTriangle::ResetPoints(const std::vector<LVector>& points) {
	this->pA = points[0];
	this->pB = points[1];
	this->pC = points[2];
}

std::ostream& operator<<(std::ostream& os, const LTriangle& info) {
	os << "{ " << info.pA << ", " << info.pB << ", " << info.pC << ", " << info.col << " }";
	return os;
}
