#ifndef LLINE_HPP
#define LLINE_HPP

#include "LShape.hpp"

class LLine : public LShape {
   public:
	LVector pA, pB;

	LLine() = default;

	LLine(float x1, float y1, float x2, float y2) : pA(x1, y1), pB(x2, y2) {}
	LLine(const LVector& pA_, const LVector& pB_) : pA(pA_), pB(pB_) {}

	LLine(const LLine& other) = default;

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

#endif	// LLINE_HPP
