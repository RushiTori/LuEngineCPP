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
	
	virtual void Rotate(float angle);

	virtual void SetCenter(const LVector& pos);

	virtual LVector GetCenter() const;
	virtual Rectangle GetBoundingBox() const;

	virtual uint GetPointsCount() const;
	virtual LVector GetPoint(uint idx) const;

	virtual bool CheckCollision(const LVector& point) const;
	virtual bool CheckCollision(const LVector& lineStart, const LVector& lineEnd) const;
	virtual bool CheckCollision(const LVector& center, float radius) const;

	virtual bool CheckCollision(const LShape& shape) const;

   protected:
	virtual void ResetPoints(const std::vector<LVector>& points);
};

std::ostream& operator<<(std::ostream& os, const LCircle& info);

#endif	// LCIRCLE_HPP
