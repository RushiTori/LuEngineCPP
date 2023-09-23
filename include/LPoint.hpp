#ifndef LPOINT_HPP
#define LPOINT_HPP

#include "LShape.hpp"

class LPoint : public LShape {
   public:
	LVector pos;

	LPoint() = default;

	LPoint(float x, float y) : pos(x, y) {}
	LPoint(const LVector& pos_) : pos(pos_) {}
	operator LVector() const { return pos; }

	LPoint(const LPoint& other) = default;

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

#endif	// LPOINT_HPP
