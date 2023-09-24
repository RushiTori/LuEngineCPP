#ifndef TEX_VIEW_HPP
#define TEX_VIEW_HPP

#include "EngineUtils.hpp"

struct TexView {
	const Texture2D* tex = nullptr;
	LVector uvCenter = LVector(0.5f, 0.5f);
	LVector uvSizes = LVector(1, 1);

	TexView() = default;
	TexView(const Texture2D* tex_, uint pixelX, uint pixelY, uint pixelWidth, uint pixelHeight);
	TexView(const Texture2D* tex_, const LVector& texPos, const LVector& texSizes);
	// TexView(const TexView& other) : tex(other.tex), uvCenter(other.uvCenter), uvSizes(other.uvSizes) {}

	Rectangle GetUVRec() const;
	LVector GetPixelPos() const;
	LVector GetPixelSizes() const;
	Rectangle GetPixelRec() const;

	void DisplayRect(float x, float y, float w, float h, LColor tint = LColor::WHITE) const;
	void DisplayRect(const LVector& pos, float w, float h, LColor tint = LColor::WHITE) const;
	void DisplayRect(const LVector& pos, const LVector& sizes, LColor tint = LColor::WHITE) const;
	void DisplayRect(const Rectangle& rec, LColor tint = LColor::WHITE) const;

	void DisplayCircle(float x, float y, float r, LColor tint = LColor::WHITE, uint pCount = 32U) const;
	void DisplayCircle(const LVector& pos, float r, LColor tint = LColor::WHITE, uint pCount = 32U) const;

	void DisplayTriangle(const LVector& pA, const LVector& pB, const LVector& pC, LColor tint = LColor::WHITE) const;

	void DisplayPoly(const LVector& center, float r, uint pCount, float angle = 0.f, LColor tint = LColor::WHITE) const;

	void DisplayPoly(const std::vector<LVector>& points, LColor tint = LColor::WHITE) const;

	void Display(const std::vector<LVector>& points, const std::vector<LVector>& uv, LColor tint = LColor::WHITE) const;
};

#endif	// TEX_VIEW_HPP
