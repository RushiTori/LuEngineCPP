#include "LPoly.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoint.hpp"
#include "LRect.hpp"
#include "LTriangle.hpp"

LPoly::LPoly(const LVector& center, float r, uint pCount, float angle) {
	if (pCount < 3) return;
	
	for (uint i = 0; i < pCount; i++) {
		this->points.push_back(center + LVector::fromAngle(angle + (TWO_PI - ((i / (float)pCount) * TWO_PI)), r));
	}
}

void LPoly::SetPos(const LVector& pos) {
	LVector center;

	for (const auto& a : this->points) {
		center += a;
	}

	center /= this->points.size();

	for (auto& a : this->points) {
		a -= center;
		a += pos;
	}
}

void LPoly::Move(const LVector& vel) {
	for (auto& a : this->points) {
		a += vel;
	}
}

LVector LPoly::GetPos() const {
	LVector center;

	for (const auto& a : this->points) {
		center += a;
	}

	center /= this->points.size();
	return center;
}

LVector LPoly::GetCenter() const {
	LVector center;

	for (const auto& a : this->points) {
		center += a;
	}

	center /= this->points.size();
	return center;
}

Rectangle LPoly::GetBoundingBox() const {
	float minX = this->points[0].x;
	float minY = this->points[0].y;

	float maxX = this->points[0].x;
	float maxY = this->points[0].y;

	for (const auto& a : this->points) {
		if (a.x < minX) minX = a.x;
		if (a.y < minY) minY = a.y;

		if (a.x > maxX) maxX = a.x;
		if (a.y > maxY) maxY = a.y;
	}

	return (Rectangle){.x = minX, .y = minY, .width = maxX - minX, .height = maxY - minY};
}

bool LPoly::CheckCollision(const LPoint& other) const { return other.CheckCollision(*this); }

bool LPoly::CheckCollision(const LLine& other) const { return other.CheckCollision(*this); }

bool LPoly::CheckCollision(const LCircle& other) const { return other.CheckCollision(*this); }

bool LPoly::CheckCollision(const LRect& other) const { return other.CheckCollision(*this); }

bool LPoly::CheckCollision(const LTriangle& other) const { return other.CheckCollision(*this); }

bool LPoly::CheckCollision(const LPoly& other) const {
	for (uint i = 0; i < this->points.size(); i++) {
		uint j = (i + 1) % this->points.size();
		if (other.CheckCollision(LLine(this->points[i], this->points[j]))) return true;
	}

	for (uint i = 0; i < other.points.size(); i++) {
		uint j = (i + 1) % other.points.size();
		if (this->CheckCollision(LLine(other.points[i], other.points[j]))) return true;
	}

	return false;
}

void LPoly::Display() const { this->skin.DisplayPoly(this->points, this->col); }

std::ostream& operator<<(std::ostream& os, const LPoly& info) {
	os << "{ " << info.points.size() << " : { ";
	for (uint i = 0; i < info.points.size(); i++) {
		os << info.points[i];
		if (i < info.points.size() - 1) os << ", ";
	}
	os << " }, " << info.col << " }" << std::endl;
	return os;
}
