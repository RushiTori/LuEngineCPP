#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(const string& texPath, uint cellW_, uint cellH_) {
	this->tex = LoadTexture(texPath.c_str());

	if (!this->tex.id) return;

	this->cellW = cellW_;
	this->cellH = cellH_;

	this->sheetW = this->tex.width / this->cellW;
	this->sheetH = this->tex.height / this->cellH;
}

SpriteSheet::~SpriteSheet() {
	UnloadTexture(this->tex);
	this->tex.id = 0;
}

const Texture2D* SpriteSheet::GetTexture() const{
  if (!this->tex.id) return nullptr;
  return &this->tex;
}

void SpriteSheet::Recut(uint cellW, uint cellH) {
	this->cellW = cellW;
	this->cellH = cellH;

	this->sheetW = this->tex.width / this->cellW;
	this->sheetH = this->tex.height / this->cellH;
}

std::optional<TexView> SpriteSheet::GetCell(uint x, uint y) const {
	if (x >= this->sheetW || y >= this->sheetH) return {};
	return TexView(&this->tex, this->cellW * x, this->cellH * y, this->cellW, this->cellH);
}
