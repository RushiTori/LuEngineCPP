#include "LPoint.hpp"

Rectangle LPoint::GetBoundingBox() const {
	return (Rectangle){.x = pos.x - 0.5f, .y = pos.y - 0.5f, .width = 1.0f, .height = 1.0f};
}

uint LPoint::GetPointsCount() const { return 1; }

LVector LPoint::GetPoint(uint idx) const {
	if (idx == 0) return this->pos;
	return LVector();
}

bool LPoint::CheckCollision(const LVector& point) const { return LVector::dist2(this->pos, point) <= (0.5f * 0.5f); }

bool LPoint::CheckCollision(const LVector& lineStart, const LVector& lineEnd) const {
	float distA = LVector::dist(lineStart, this->pos);
	float distB = LVector::dist(lineEnd, this->pos);

	float distAB = distA + distB;

	float realDist = LVector::dist(lineStart, lineEnd);

	return ((distAB >= realDist - 0.05f) && (distAB <= realDist + 0.05f));
}

bool LPoint::CheckCollision(const LVector& center, float radius) const {
	return LVector::dist2(this->pos, center) <= (radius * radius);
}

bool LPoint::CheckCollision(const LShape& shape) const { return shape.CheckCollision(this->pos); }

void LPoint::Display() const { DrawCircleV(this->pos, 0.1, this->col); }

void LPoint::ResetPoints(const std::vector<LVector>& points) { this->pos = points[0]; }

std::ostream& operator<<(std::ostream& os, const LPoint& info) {
	os << "{ " << info.pos << ", " << info.col << " }";
	return os;
}
