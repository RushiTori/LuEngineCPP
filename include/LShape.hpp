#ifndef LSHAPE_HPP
#define LSHAPE_HPP

#include "TexView.hpp"

class LPoint;
class LLine;
class LCircle;
class LRect;
class LTriangle;
class LPoly;

class LShape {
   protected:
	TexView skin;

   public:
	LColor col;

	LShape() = default;
	LShape(const LShape& other) = default;
	virtual ~LShape() {}

	virtual void SetTexture(const Texture2D* tex) final;
	virtual void SetTexture(const Texture2D* tex, uint x, uint y, uint w, uint h) final;
	virtual void SetSkin(const TexView& skin) final;

	virtual void SetCenter(const LVector& pos) = 0;
	virtual void Move(const LVector& vel) = 0;

	virtual LVector GetCenter() const = 0;
	virtual Rectangle GetBoundingBox() const = 0;

	virtual uint GetPointsCount() const = 0;
	virtual LVector GetPoint(uint idx) const = 0;
	virtual std::vector<LVector> GetPoints() const = 0;

	virtual bool CheckCollision(const LVector& point) const;

	virtual bool CheckCollision(const LVector& lineStart, const LVector& lineEnd) const;
	virtual bool CheckCollision(const LLine& other) const final;

	virtual bool CheckCollision(const LVector& center, float radius) const;
	virtual bool CheckCollision(const LCircle& other) const final;

	virtual bool CheckCollision(const LShape& shape) const;

	/*virtual bool CheckCollision(const LPoint& other) const = 0;
	virtual bool CheckCollision(const LLine& other) const = 0;
	virtual bool CheckCollision(const LCircle& other) const = 0;
	virtual bool CheckCollision(const LRect& other) const = 0;
	virtual bool CheckCollision(const LTriangle& other) const = 0;
	virtual bool CheckCollision(const LPoly& other) const = 0;*/

	virtual void Display() const;
};

#endif	// LSHAPE_HPP
