#include "LCircle.hpp"

void LCircle::Rotate(float angle) { this->angle += angle; }

void LCircle::SetCenter(const LVector& pos) { this->pos = pos; }

LVector LCircle::GetCenter() const { return this->pos; }

Rectangle LCircle::GetBoundingBox() const {
	return (Rectangle){.x = this->pos.x - r, .y = this->pos.y - r, .width = r * 2, .height = r * 2};
}

uint LCircle::GetPointsCount() const { return 32; }

LVector LCircle::GetPoint(uint idx) const {
	uint pCount = GetPointsCount();
	if (idx >= pCount) return LVector();
	float pAngle = TWO_PI - ((idx / (float)pCount) * TWO_PI);
	return this->pos + LVector::fromAngle(this->angle + pAngle, this->r);
}

bool LCircle::CheckCollision(const LVector& point) const {
	return LVector::dist2(this->pos, point) <= (this->r * this->r);
}

bool LCircle::CheckCollision(const LVector& lineStart, const LVector& lineEnd) const {
	if (CheckCollision(lineStart) || CheckCollision(lineEnd)) return true;

	LVector AtoB = lineEnd - lineStart;
	LVector AtoCenter = this->pos - lineStart;

	float dotScale = LVector::dot(AtoCenter, AtoB.norm());
	if ((dotScale < 0) || ((dotScale * dotScale) > AtoB.mag2())) return false;

	LVector ConAB = lineStart + AtoB.setMag(dotScale);

	return (LVector::dist2(ConAB, this->pos) <= (this->r * this->r));
}

bool LCircle::CheckCollision(const LVector& center, float radius) const {
	return LVector::dist2(this->pos, center) <= ((this->r + radius) * (this->r + radius));
}

bool LCircle::CheckCollision(const LShape& shape) const { return shape.CheckCollision(this->pos, this->r); }

void LCircle::ResetPoints([[maybe_unused]] const std::vector<LVector>& points) {}

std::ostream& operator<<(std::ostream& os, const LCircle& info) {
	os << "{ " << info.pos << ", " << info.r << ", " << info.col << " }";
	return os;
}
