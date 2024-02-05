#ifndef WORLD_CAMERA_HPP
#define WORLD_CAMERA_HPP

#include "LVector.hpp"

class WorldCamera : public Camera2D {
   public:
	WorldCamera(const LVector& centerPos, float zoom);

	void Pan(const LVector& amount);
	void MoveTo(const LVector& newCenter);

	void Zoom(float amount);
	void ZoomTowards(const LVector& pos, float amount);

	LVector WorldPos(const LVector& screenPos) const;
	LVector WorldMousePos() const;

	LVector WorldViewOffset() const;
	LVector WorldViewSize() const;
	LVector WorldViewCenter() const;
	Rectangle WorldViewBounds() const;
};

#endif	// WORLD_CAMERA_HPP
