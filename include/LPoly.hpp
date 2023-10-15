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

	virtual uint GetPointsCount() const;
	virtual LVector GetPoint(uint idx) const;

   protected:
	virtual void ResetPoints(const std::vector<LVector>& points);
};

std::ostream& operator<<(std::ostream& os, const LPoly& info);

#endif	// LPOLY_HPP
