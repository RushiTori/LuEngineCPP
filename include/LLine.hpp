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

std::ostream& operator<<(std::ostream& os, const LLine& info);

#endif	// LLINE_HPP
