#ifndef LSHAPE_HPP
#define LSHAPE_HPP

#include "TexView.hpp"

class LLine;
class LCircle;

class LShape {
   protected:
	TexView skin;
	float angle;

   public:
	LColor col;

	LShape() = default;
	LShape(const LShape& other) = default;
	virtual ~LShape() {}

	virtual void SetTexture(const Texture2D* tex) final;
	virtual void SetTexture(const Texture2D* tex, uint x, uint y, uint w, uint h) final;
	virtual void SetSkin(const TexView& skin) final;

	virtual void SetRotation(float angle);
	virtual void Rotate(float angle);
	virtual void Rotate(float angle, const LVector& anchor);

	virtual void SetCenter(const LVector& pos);
	virtual void Move(const LVector& vel);

	virtual float GetAngle() const final;
	virtual LVector GetCenter() const;
	virtual Rectangle GetBoundingBox() const;

	virtual uint GetPointsCount() const = 0;
	virtual LVector GetPoint(uint idx) const = 0;
	virtual std::vector<LVector> GetPoints() const final;

	virtual bool CheckCollision(const LVector& point) const;

	virtual bool CheckCollision(const LVector& lineStart, const LVector& lineEnd) const;
	virtual bool CheckCollision(const LLine& other) const final;

	virtual bool CheckCollision(const LVector& center, float radius) const;
	virtual bool CheckCollision(const LCircle& other) const final;

	virtual bool CheckCollision(const LShape& shape) const;

	virtual void Display() const;

   protected:
	virtual void ResetPoints(const std::vector<LVector>& points) = 0;
};

#endif	// LSHAPE_HPP
