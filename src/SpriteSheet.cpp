#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet() : tex({0}), cellWidth(0), cellHeight(0), sheetWidth(0), sheetHeight(0) {}

SpriteSheet::SpriteSheet(const std::string& filePath, uint32_t cellWidth_, uint32_t cellHeight_) : SpriteSheet() {
	Load(filePath, cellWidth_, cellHeight_);
}

SpriteSheet::~SpriteSheet() { Unload(); }

uint32_t SpriteSheet::GetSheetWidth() const { return sheetWidth; }

uint32_t SpriteSheet::GetSheetHeight() const { return sheetHeight; }

void SpriteSheet::Load(const std::string& filePath, uint32_t cellWidth_, uint32_t cellHeight_) {
	Unload();

	tex = LoadTexture(filePath.c_str());
	if (!tex.id) return;

	cellWidth = cellWidth_;
	cellHeight = cellHeight_;
	sheetWidth = tex.width / cellWidth;
	sheetHeight = tex.height / cellHeight;
}

void SpriteSheet::Unload() {
	UnloadTexture(tex);
	tex = {0};
	cellWidth = 0;
	cellHeight = 0;
	sheetWidth = 0;
	sheetHeight = 0;
}

TexView SpriteSheet::GetTexView(uint32_t tIdx, uint32_t tW, uint32_t tH) const {
	return GetTexView(tIdx % sheetWidth, tIdx / sheetWidth, tW, tH);
}

TexView SpriteSheet::GetTexView(uint32_t tX, uint32_t tY, uint32_t tW, uint32_t tH) const {
	TexView view = (TexView){
		.tex = &tex,
		.source =
			(Rectangle){
				.x = (float)tX * cellWidth,
				.y = (float)tY * cellHeight,
				.width = (float)std::min(tW * cellWidth, (uint32_t)tex.width),
				.height = (float)std::min(tH * cellHeight, (uint32_t)tex.height),
			},
	};
	if (tX > sheetWidth || tY > sheetHeight) view.tex = nullptr;
	return view;
}
