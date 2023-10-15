#ifndef LTRIANGLE_HPP
#define LTRIANGLE_HPP

#include "LShape.hpp"

class LTriangle : public LShape {
   public:
	LVector pA, pB, pC;

	LTriangle() = default;

	LTriangle(const LVector& pA_, const LVector& pB_, const LVector& pC_) : pA(pA_), pB(pB_), pC(pC_) {}

	LTriangle(const LTriangle& other) = default;

	virtual uint GetPointsCount() const;
	virtual LVector GetPoint(uint idx) const;

   protected:
	virtual void ResetPoints(const std::vector<LVector>& points);
};

std::ostream& operator<<(std::ostream& os, const LTriangle& info);

#endif	// LTRIANGLE_HPP
