#ifndef LTRIANGLE_HPP
#define LTRIANGLE_HPP

#include "LShape.hpp"

class LTriangle : public LShape {
   public:
	LVector pA, pB, pC;

	LTriangle() = default;

	LTriangle(const LVector& pA_, const LVector& pB_, const LVector& pC_) : pA(pA_), pB(pB_), pC(pC_) {}

	LTriangle(const LTriangle& other) = default;

	virtual void SetPos(const LVector& pos);
	virtual void Move(const LVector& vel);

	virtual LVector GetPos() const;
	virtual LVector GetCenter() const;
	virtual Rectangle GetBoundingBox() const;

	virtual bool CheckCollision(const LPoint& other) const;
	virtual bool CheckCollision(const LLine& other) const;
	virtual bool CheckCollision(const LCircle& other) const;
	virtual bool CheckCollision(const LRect& other) const;
	virtual bool CheckCollision(const LTriangle& other) const;
	virtual bool CheckCollision(const LPoly& other) const;

	virtual void Display() const;
};

std::ostream& operator<<(std::ostream& os, const LTriangle& info);

#endif	// LTRIANGLE_HPP
