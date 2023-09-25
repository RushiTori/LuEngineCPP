#include "LRect.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoint.hpp"
#include "LPoly.hpp"
#include "LTriangle.hpp"

void LRect::SetCenter(const LVector& pos) {
	this->x = pos.x - this->w / 2;
	this->y = pos.y - this->h / 2;
}

void LRect::Move(const LVector& vel) {
	this->x += vel.x;
	this->y += vel.y;
}

LVector LRect::GetCenter() const { return LVector(this->x + this->w / 2, this->y + this->h / 2); }

Rectangle LRect::GetBoundingBox() const { return *this; }

uint LRect::GetPointsCount() const { return 4; }

LVector LRect::GetPoint(uint idx) const {
	if (idx == 0) return LVector(this->x, this->y);
	if (idx == 1) return LVector(this->x, this->y + this->h);
	if (idx == 2) return LVector(this->x + this->w, this->y + this->h);
	if (idx == 3) return LVector(this->x + this->w, this->y);
	return LVector();
}

std::vector<LVector> LRect::GetPoints() const {
	return {LVector(this->x, this->y), LVector(this->x, this->y + this->h),
			LVector(this->x + this->w, this->y + this->h), LVector(this->x + this->w, this->y)};
}

void LRect::Display() const { this->skin.DisplayRect(*this, this->col); }

std::ostream& operator<<(std::ostream& os, const LRect& info) {
	os << "{ " << info.x << ", " << info.y << ", " << info.w << ", " << info.h << ", " << info.col << " }";
	return os;
}
