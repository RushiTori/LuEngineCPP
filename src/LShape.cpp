#include "LShape.hpp"

#include "LCircle.hpp"
#include "LLine.hpp"
#include "LPoint.hpp"

void LShape::SetTexture(const Texture2D* tex) { SetTexture(tex, 0, 0, tex->width, tex->height); }

void LShape::SetTexture(const Texture2D* tex, uint x, uint y, uint w, uint h) { this->skin = TexView(tex, x, y, w, h); }

void LShape::SetSkin(const TexView& skin) {
	if (skin.tex) this->skin = skin;
}

bool LShape::CheckCollision(const LVector& point) const {
	uint pCount = GetPointsCount();

	int firstSide = 0;

	for (uint i = 0; i < pCount; i++) {
		uint j = (i + 1) % pCount;
		LVector pA = GetPoint(i);
		LVector pB = GetPoint(j);

		LVector AtoB = pB - pA;
		LVector AtoPoint = point - pA;

		int currSide = AtoPoint.side(AtoB);

		if (i == 0) {
			firstSide = currSide;
			continue;
			;
		}

		if (currSide != firstSide) return false;
	}

	return true;
}

bool LShape::CheckCollision(const LVector& lineStart, const LVector& lineEnd) const {
	if (CheckCollision(lineStart) || CheckCollision(lineEnd)) return true;

	float lineDistY = lineEnd.y - lineStart.y;
	float lineDistX = lineEnd.x - lineStart.x;

	uint pCount = GetPointsCount();
	for (uint i = 0; i < pCount; i++) {
		uint j = (i + 1) % pCount;
		LVector pA = GetPoint(i);
		LVector pB = GetPoint(j);

		float denom = (lineDistY * (pB.x - pA.x)) - (lineDistX * (pB.y - pA.y));
		float uA = (lineDistX * (pA.y - lineStart.y) - lineDistY * (pA.x - lineStart.x)) / denom;
		float uB = ((pB.x - pA.x) * (pA.y - lineStart.y) - (pB.y - pA.y) * (pA.x - lineStart.x)) / denom;
		if ((uA > 0 && uA < 1) && (uB > 0 && uB < 1)) return true;
	}

	return false;
}

bool LShape::CheckCollision(const LLine& line) const { return CheckCollision(line.pA, line.pB); }

bool LShape::CheckCollision(const LVector& center, float radius) const {
	if (CheckCollision(center)) return true;

	uint pCount = GetPointsCount();
	for (uint i = 0; i < pCount; i++) {
		uint j = (i + 1) % pCount;
		LVector pA = GetPoint(i);
		if (LVector::dist2(pA, center) <= (radius * radius)) return true;

		LVector pB = GetPoint(j);

		LVector AtoB = pB - pA;
		LVector AtoCenter = center - pA;

		float dotScale = LVector::dot(AtoCenter, AtoB);
		if (dotScale <= 0 || dotScale >= AtoB.mag()) continue;

		LVector ConAB = AtoB.setMag(dotScale);

		if (LVector::dist2(ConAB, center) <= (radius * radius)) return true;
	}

	return false;
}

bool LShape::CheckCollision(const LCircle& circle) const { return CheckCollision(circle.pos, circle.r); }

bool LShape::CheckCollision(const LShape& shape) const {
	uint pCount = GetPointsCount();

	for (uint i = 0; i < pCount; i++) {
		uint j = (i + 1) % pCount;
		LVector pA = GetPoint(i);
		LVector pB = GetPoint(j);
		if (shape.CheckCollision(pA, pB)) return true;
	}

	pCount = shape.GetPointsCount();

	for (uint i = 0; i < pCount; i++) {
		if (CheckCollision(shape.GetPoint(i))) return true;
	}

	return false;
}

void LShape::Display() const {}
