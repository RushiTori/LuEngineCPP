#include "WorldCamera.hpp"

#include "EngineUtils.hpp"

WorldCamera::WorldCamera(const LVector& centerPos, float zoom) {
	this->offset = GetScreenSizes() / 2;
	this->target = centerPos;
	this->rotation = 0;
	this->zoom = zoom;
}

void WorldCamera::Pan(const LVector& amount) { target = LVector(target) + amount / zoom; }

void WorldCamera::MoveTo(const LVector& newCenter) { target = newCenter; }

void WorldCamera::Zoom(float amount) { zoom *= amount; }

void WorldCamera::ZoomTowards(const LVector& pos, float amount) {
	LVector basePos = GetWorldToScreen2D(pos, *this);
	zoom *= amount;
	target = LVector(target) + pos - WorldPos(basePos);
}

LVector WorldCamera::WorldPos(const LVector& screenPos) const { return GetScreenToWorld2D(screenPos, *this); }

LVector WorldCamera::WorldMousePos() const { return WorldPos(GetMousePosition()); }

LVector WorldCamera::WorldViewOffset() const { return WorldPos(LVector(0, 0)); }

LVector WorldCamera::WorldViewSize() const { return WorldPos(GetScreenSizes()) - WorldViewOffset(); }

LVector WorldCamera::WorldViewCenter() const { return WorldPos(GetScreenSizes() / 2); }

Rectangle WorldCamera::WorldViewBounds() const {
	LVector wOff = WorldViewOffset();
	LVector wSize = WorldViewSize();
	return (Rectangle){.x = wOff.x, .y = wOff.y, .width = wSize.x, .height = wSize.y};
}
