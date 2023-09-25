#ifndef LPOLY_HPP
#define LPOLY_HPP

#include "LShape.hpp"

class LPoly : public LShape {
   public:
	std::vector<LVector> points;

	LPoly() = default;

	LPoly(const LVector& center, float r, uint pCount, float angle = 0);
	LPoly(const std::vector<LVector>& points_) : points(points_) {}

	LPoly(const LPoly& other) = default;

	virtual void SetCenter(const LVector& pos);
	virtual void Move(const LVector& vel);

	virtual LVector GetCenter() const;
	virtual Rectangle GetBoundingBox() const;

	virtual uint GetPointsCount() const;
	virtual LVector GetPoint(uint idx) const;
	virtual std::vector<LVector> GetPoints() const;

	virtual void Display() const;
};

std::ostream& operator<<(std::ostream& os, const LPoly& info);

#endif	// LPOLY_HPP
