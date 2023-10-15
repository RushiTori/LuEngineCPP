#include "LPoly.hpp"

LPoly::LPoly(const LVector& center, float r, uint pCount, float angle) {
	if (pCount < 3) return;

	for (uint i = 0; i < pCount; i++) {
		float pAngle = TWO_PI - ((i / (float)pCount) * TWO_PI);
		this->points.push_back(center + LVector::fromAngle(angle + pAngle, r));
	}
}

uint LPoly::GetPointsCount() const { return this->points.size(); }

LVector LPoly::GetPoint(uint idx) const {
	if (idx >= GetPointsCount()) return LVector();
	return points[idx];
}

void LPoly::ResetPoints(const std::vector<LVector>& points) { this->points = points; }

std::ostream& operator<<(std::ostream& os, const LPoly& info) {
	os << "{ " << info.points.size() << " : { ";
	for (uint i = 0; i < info.points.size(); i++) {
		os << info.points[i];
		if (i < info.points.size() - 1) os << ", ";
	}
	os << " }, " << info.col << " }" << std::endl;
	return os;
}
