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

	virtual void SetCenter(const LVector& pos);
	virtual void Move(const LVector& vel);

	virtual LVector GetCenter() const;
	virtual Rectangle GetBoundingBox() const;

	virtual uint GetPointsCount() const;
	virtual LVector GetPoint(uint idx) const;
	virtual std::vector<LVector> GetPoints() const;

	virtual bool CheckCollision(const LVector& point) const;
	virtual bool CheckCollision(const LVector& lineStart, const LVector& lineEnd) const;
	virtual bool CheckCollision(const LVector& center, float radius) const;

	virtual bool CheckCollision(const LShape& shape) const;

	virtual void Display() const;
};

std::ostream& operator<<(std::ostream& os, const LPoint& info);

#endif	// LPOINT_HPP
