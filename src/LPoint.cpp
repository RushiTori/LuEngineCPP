#include "LPoint.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoly.hpp"
#include "LRect.hpp"
#include "LTriangle.hpp"

void LPoint::SetCenter(const LVector& pos) { this->pos = pos; }

void LPoint::Move(const LVector& vel) { this->pos += vel; }

LVector LPoint::GetCenter() const { return pos; }

Rectangle LPoint::GetBoundingBox() const {
	return (Rectangle){.x = pos.x - 0.5f, .y = pos.y - 0.5f, .width = 0.5f, .height = 0.5f};
}

uint LPoint::GetPointsCount() const { return 1; }

LVector LPoint::GetPoint(uint idx) const {
	if (idx == 0) return this->pos;
	return LVector();
}

std::vector<LVector> LPoint::GetPoints() const { return {this->pos}; }

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

void LPoint::Display() const { this->skin.DisplayCircle(this->pos, 0.1, this->col); }

std::ostream& operator<<(std::ostream& os, const LPoint& info) {
	os << "{ " << info.pos << ", " << info.col << " }";
	return os;
}
