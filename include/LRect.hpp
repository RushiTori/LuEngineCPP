#ifndef LRECT_HPP
#define LRECT_HPP

#include "LShape.hpp"

class LRect : public LShape {
   public:
	float x, y, w, h;

	LRect() = default;

	LRect(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {}
	LRect(const LVector& pos, const LVector& sizes) : x(pos.x), y(pos.y), w(sizes.x), h(sizes.y) {}
	LRect(const Rectangle& rec) : x(rec.x), y(rec.y), w(rec.width), h(rec.height) {}

	operator Rectangle() const { return (Rectangle){.x = this->x, .y = this->y, .width = this->w, .height = this->h}; }

	LRect(const LRect& other) = default;

	virtual void SetCenter(const LVector& pos);
	virtual void Move(const LVector& vel);

	virtual LVector GetCenter() const;
	virtual Rectangle GetBoundingBox() const;

	virtual uint GetPointsCount() const;
	virtual LVector GetPoint(uint idx) const;
	virtual std::vector<LVector> GetPoints() const;

	virtual void Display() const;
};

std::ostream& operator<<(std::ostream& os, const LRect& info);

#endif	// LRECT_HPP
