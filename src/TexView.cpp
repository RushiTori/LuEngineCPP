#include "TexView.hpp"

bool TexView::IsBlank() const {
	if (!tex) return true;
	Image img = LoadImageFromTexture(*tex);
	Color* pixels = LoadImageColors(img);
	if (!pixels) return true;

	bool result = true;

	for (int32_t y = 0; y < (int32_t)source.height; y++) {
		int32_t pY = y + source.y;
		if (pY >= img.height) continue;
		for (int32_t x = 0; x < (int32_t)source.width; x++) {
			int32_t pX = x + source.x;
			if (pX >= img.width) continue;

			if (LColor(pixels[pX + pY * img.width]) != LColor(BLANK)) {
				result = false;
				break;
			}
		}
	}

	UnloadImageColors(pixels);
	UnloadImage(img);
	return result;
}

void TexView::Display(const LVector& pos, const LColor& tint) const { Display(pos, 0, LVector(1, 1), LVector(), tint); }

void TexView::Display(const LVector& pos, float scaleX, float scaleY, const LColor& tint) const {
	Display(pos, 0, LVector(scaleX, scaleY), LVector(), tint);
}

void TexView::Display(const LVector& pos, const LVector& scales, const LColor& tint) const {
	Display(pos, 0, scales, LVector(), tint);
}

void TexView::Display(const LVector& pos, float rotation, const LVector& origin, const LColor& tint) const {
	Display(pos, rotation, LVector(1, 1), origin, tint);
}

void TexView::Display(const LVector& pos, float rotation, float scaleX, float scaleY, const LVector& origin,
					  const LColor& tint) const {
	Display(pos, rotation, LVector(scaleX, scaleY), origin, tint);
}

void TexView::Display(const LVector& pos, float rotation, const LVector& scales, const LVector& origin,
					  const LColor& tint) const {
	Display(
		(Rectangle){
			.x = pos.x,
			.y = pos.y,
			.width = source.width * scales.x,
			.height = source.height * scales.y,
		},
		rotation, origin, tint);
}

void TexView::Display(const Rectangle& dest, const LColor& tint) const { Display(dest, 0, LVector(), tint); }

void TexView::Display(const Rectangle& dest, float rotation, const LVector& origin, const LColor& tint) const {
	DrawTexturePro(*tex, source, dest, origin, rotation * RAD2DEG, tint);
}
