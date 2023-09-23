#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include "TexView.hpp"

class SpriteSheet {
   private:
	Texture2D tex = {.id = 0, .width = 0, .height = 0, .mipmaps = 0, .format = 0};

	uint cellW = 0, cellH = 0;
	uint sheetW = 0, sheetH = 0;

   public:
	SpriteSheet() = default;

	SpriteSheet(const string& texPath, uint cellW_, uint cellH_);

	~SpriteSheet();

	SpriteSheet(const SpriteSheet& other) = default;

	const Texture2D* GetTexture() const;

	void Recut(uint cellW, uint cellH);

	std::optional<TexView> GetCell(uint x, uint y) const;
};

#endif	// SPRITE_SHEET_HPP
