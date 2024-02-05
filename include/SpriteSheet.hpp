#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include "TexView.hpp"

class SpriteSheet {
   protected:
	Texture tex;
	uint32_t cellWidth, cellHeight;
	uint32_t sheetWidth, sheetHeight;

   public:
	SpriteSheet(const SpriteSheet& other) = delete;
	SpriteSheet();
	SpriteSheet(const std::string& filePath, uint32_t cellWidth_ = 1, uint32_t cellHeight_ = 1);
	~SpriteSheet();

	uint32_t GetSheetWidth() const;
	uint32_t GetSheetHeight() const;

	void Load(const std::string& filePath, uint32_t cellWidth_ = 1, uint32_t cellHeight_ = 1);
	void Unload();

	TexView GetTexView(uint32_t tIdx, uint32_t tW = 1, uint32_t tH = 1) const;
	TexView GetTexView(uint32_t tX, uint32_t tY, uint32_t tW = 1, uint32_t tH = 1) const;
};

#endif	// SPRITE_SHEET_HPP
