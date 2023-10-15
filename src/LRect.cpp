#include "LRect.hpp"

void LRect::Rotate(float angle) { this->angle += angle; }

void LRect::Move(const LVector& vel) {
	this->x += vel.x;
	this->y += vel.y;
}

uint LRect::GetPointsCount() const { return 4; }

LVector LRect::GetPoint(uint idx) const {
	LVector center(this->x + (this->w / 2), this->y + (this->h / 2));
	if (idx == 0) return center + (LVector(-this->w, -this->h).rotate(this->angle) / 2);
	if (idx == 1) return center + (LVector(this->w, -this->h).rotate(this->angle) / 2);
	if (idx == 2) return center + (LVector(this->w, this->h).rotate(this->angle) / 2);
	if (idx == 3) return center + (LVector(-this->w, this->h).rotate(this->angle) / 2);
	return LVector();
}

void LRect::Display() const { this->skin.DisplayRect(*this, this->angle, 0, this->col); }

void LRect::ResetPoints([[maybe_unused]] const std::vector<LVector>& points) {}

std::ostream& operator<<(std::ostream& os, const LRect& info) {
	os << "{ " << info.x << ", " << info.y << ", " << info.w << ", " << info.h << ", " << info.col << " }";
	return os;
}
