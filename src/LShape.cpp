#include "LShape.hpp"

void LShape::SetTexture(const Texture2D* tex) {
  SetTexture(tex, 0, 0, tex->width, tex->height);
}

void LShape::SetTexture(const Texture2D* tex, uint x, uint y, uint w, uint h) {
  this->skin = TexView(tex, x, y, w, h);
}

void LShape::Display() const {}
