#ifndef LCIRCLE_HPP
#define LCIRCLE_HPP

#include "LShape.hpp"

class LCircle : public LShape {
   public:
	LVector pos;
	float r;

	LCircle() = default;

	LCircle(float x_, float y_, float r_) : pos(x_, y_), r(r_) {}
	LCircle(const LVector& pos_, float r_) : pos(pos_), r(r_) {}

	LCircle(const LCircle& other) = default;

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

#endif	// LCIRCLE_HPP
