#include "LPoint.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoly.hpp"
#include "LRect.hpp"
#include "LTriangle.hpp"

void LPoint::SetPos(const LVector& pos) { this->pos = pos; }

void LPoint::Move(const LVector& vel) { this->pos += vel; }

LVector LPoint::GetPos() const { return pos; }

LVector LPoint::GetCenter() const { return pos; }

Rectangle LPoint::GetBoundingBox() const {
	return (Rectangle){.x = pos.x - 0.5f, .y = pos.y - 0.5f, .width = 0.5f, .height = 0.5f};
}

bool LPoint::CheckCollision(const LPoint& other) const { return other.pos == this->pos; }

bool LPoint::CheckCollision(const LLine& other) const {
	float dA = LVector::dist(this->pos, other.pA);
	float dB = LVector::dist(this->pos, other.pB);
	float realD = LVector::dist(other.pA, other.pB);

	return (dA + dB <= realD + 0.05f) && (dA + dB >= realD - 0.05f);
}

bool LPoint::CheckCollision(const LCircle& other) const {
	return LVector::dist2(this->pos, other.pos) <= (other.r * other.r);
}

bool LPoint::CheckCollision(const LRect& other) const {
	return (((this->pos.x >= other.x) && (this->pos.x <= (other.x + other.w))) &&
			((this->pos.y >= other.y) && (this->pos.y <= (other.y + other.h))));
}

bool LPoint::CheckCollision(const LTriangle& other) const {
	int sideAB = (this->pos - other.pA).side(other.pA, other.pB);
	int sideBC = (this->pos - other.pB).side(other.pB, other.pC);
	int sideCA = (this->pos - other.pC).side(other.pC, other.pA);

	return ((sideAB == sideBC) && (sideAB == sideCA));
}

bool LPoint::CheckCollision(const LPoly& other) const {
	int posSide = (this->pos - other.points[0]).side(other.points[0], other.points[1]);

	for (uint i = 1; i < other.points.size(); i++) {
		uint j = (i + 1) % other.points.size();
		int side = (this->pos - other.points[i]).side(other.points[i], other.points[j]);
		if (side != posSide) return false;
	}

	return true;
}

void LPoint::Display() const { this->skin.DisplayCircle(this->pos, 0.1, this->col); }

std::ostream& operator<<(std::ostream& os, const LPoint& info) {
	os << "{ " << info.pos << ", " << info.col << " }";
	return os;
}
