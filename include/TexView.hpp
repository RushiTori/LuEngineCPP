#ifndef TEX_VIEW_HPP
#define TEX_VIEW_HPP

#include "EngineUtils.hpp"

struct TexView {
	const Texture* tex = nullptr;
	Rectangle source = (Rectangle){
		.x = 0.0f,
		.y = 0.0f,
		.width = 0.0f,
		.height = 0.0f,
	};

	bool IsBlank() const;

	void Display(const LVector& pos, const LColor& tint = WHITE) const;

	void Display(const LVector& pos, float scaleX, float scaleY, const LColor& tint = WHITE) const;
	void Display(const LVector& pos, const LVector& scales, const LColor& tint = WHITE) const;

	void Display(const LVector& pos, float rotation, const LVector& origin = LVector(),
				 const LColor& tint = WHITE) const;
	void Display(const LVector& pos, float rotation, float scaleX, float scaleY, const LVector& origin = LVector(),
				 const LColor& tint = WHITE) const;
	void Display(const LVector& pos, float rotation, const LVector& scales, const LVector& origin = LVector(),
				 const LColor& tint = WHITE) const;

	void Display(const Rectangle& dest, const LColor& tint = WHITE) const;
	void Display(const Rectangle& dest, float rotation, const LVector& origin = LVector(),
				 const LColor& tint = WHITE) const;
};

#endif	// TEX_VIEW_HPP
