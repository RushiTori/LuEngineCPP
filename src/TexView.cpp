#include "TexView.hpp"

TexView::TexView(const Texture2D* tex_, uint pixelX, uint pixelY, uint pixelWidth, uint pixelHeight)
	: TexView(tex_, LVector(pixelX / (float)(tex_->width), pixelY / (float)(tex_->height)),
			  LVector(pixelWidth / (float)(tex_->width), pixelHeight / (float)(tex_->height))) {}

TexView::TexView(const Texture2D* tex_, const LVector& texPos, const LVector& texSizes)
	: tex(tex_), uvCenter(texPos + (texSizes / 2)), uvSizes(texSizes) {}

Rectangle TexView::GetUVRec() const {
	return (Rectangle){.x = this->uvCenter.x - (this->uvSizes.x / 2),
					   .y = this->uvCenter.y - (this->uvSizes.y / 2),
					   .width = this->uvSizes.x,
					   .height = this->uvSizes.y};
}

LVector TexView::GetPixelPos() const {
	return (this->uvCenter - (this->uvSizes / 2)) * LVector(this->tex->width, this->tex->height);
}

LVector TexView::GetPixelSizes() const { return this->uvSizes * LVector(this->tex->width, this->tex->height); }

Rectangle TexView::GetPixelRec() const {
	LVector pos = GetPixelPos();
	LVector sizes = GetPixelSizes();
	return (Rectangle){.x = pos.x, .y = pos.y, .width = sizes.x, .height = sizes.y};
}

void TexView::DisplayRect(float x, float y, float w, float h, LColor tint) const {
	DisplayRect((Rectangle){.x = x, .y = y, .width = w, .height = h}, tint);
}

void TexView::DisplayRect(const LVector& pos, float w, float h, LColor tint) const {
	DisplayRect((Rectangle){.x = pos.x, .y = pos.y, .width = w, .height = h}, tint);
}

void TexView::DisplayRect(const LVector& pos, const LVector& sizes, LColor tint) const {
	DisplayRect((Rectangle){.x = pos.x, .y = pos.y, .width = sizes.x, .height = sizes.y}, tint);
}

void TexView::DisplayRect(const Rectangle& rec, LColor tint) const {
	const LVector center(rec.x + (rec.width / 2), rec.y + (rec.height / 2));

	const std::vector<LVector> points{LVector(rec.x, rec.y), LVector(rec.x, rec.y + rec.height),
									  LVector(rec.x + rec.width, rec.y + rec.height),
									  LVector(rec.x + rec.width, rec.y)};

	const Rectangle uvRec = GetUVRec();

	const std::vector<LVector> uv{LVector(uvRec.x, uvRec.y), LVector(uvRec.x, uvRec.y + uvRec.height),
								  LVector(uvRec.x + uvRec.width, uvRec.y + uvRec.height),
								  LVector(uvRec.x + uvRec.width, uvRec.y)};

	Display(center, points, uv, tint);
}

void TexView::DisplayCircle(float x, float y, float r, LColor tint, uint pCount) const {
	DisplayCircle(LVector(x, y), r, tint, pCount);
}

void TexView::DisplayCircle(const LVector& pos, float r, LColor tint, uint pCount) const {
	DisplayPoly(pos, r, pCount, 0.0f, tint);
}

void TexView::DisplayTriangle(const LVector& pA, const LVector& pB, const LVector& pC, LColor tint) const {
	const LVector center((pA + pB + pC) / 3);

	const std::vector<LVector> points{pA, pB, pC};

	float minX = std::min(pA.x, std::min(pB.x, pC.x));
	float minY = std::min(pA.y, std::min(pB.y, pC.y));
	const LVector minVec(minX, minY);

	float maxX = std::max(pA.x, std::max(pB.x, pC.x));
	float maxY = std::max(pA.y, std::max(pB.y, pC.y));
	const LVector maxVec(maxX, maxY);

	const Rectangle uvRec = GetUVRec();
	const LVector minUV(uvRec.x, uvRec.y);
	const LVector maxUV(uvRec.x + uvRec.width, uvRec.y + uvRec.height);

	const std::vector<LVector> uv{LVector::map(pA, minVec, maxVec, minUV, maxUV),
								  LVector::map(pB, minVec, maxVec, minUV, maxUV),
								  LVector::map(pC, minVec, maxVec, minUV, maxUV)};

	Display(center, points, uv, tint);
}

void TexView::DisplayPoly(const LVector& center, float r, uint pCount, float angle, LColor tint) const {
	if (pCount < 3) return;

	const Rectangle uvRec = GetUVRec();
	const LVector minUV(uvRec.x, uvRec.y);
	const LVector maxUV(uvRec.x + uvRec.width, uvRec.y + uvRec.height);

	std::vector<LVector> points(pCount), uv(pCount);

	for (uint i = 0; i < pCount; i++) {
		float tempAngle = TWO_PI - ((i / (float)pCount) * TWO_PI);
		LVector tempPoint = LVector::fromAngle(angle + tempAngle, r);
		LVector tempUV = LVector::map(tempPoint.norm(), LVector(-1, -1), LVector(1, 1), minUV, maxUV);

		points.push_back(tempPoint);
		uv.push_back(tempUV);
	}

	Display(center, points, uv, tint);
}

void TexView::DisplayPoly(const std::vector<LVector>& points, LColor tint) const {
	if (points.size() < 3) return;

	const Rectangle uvRec = GetUVRec();
	const LVector minUV(uvRec.x, uvRec.y);
	const LVector maxUV(uvRec.x + uvRec.width, uvRec.y + uvRec.height);

	LVector center;
	LVector minVec, maxVec;

	for (const auto& p : points) {
		center += p;

		if (p.x < minVec.x) minVec.x = p.x;
		if (p.y < minVec.y) minVec.y = p.y;

		if (p.x > maxVec.x) maxVec.x = p.x;
		if (p.y > maxVec.y) maxVec.y = p.y;
	}

	center /= points.size();

	std::vector<LVector> uv(points.size());

	for (const auto& p : points) {
		uv.push_back(LVector::map(p, minVec, maxVec, minUV, maxUV));
	}

	Display(center, points, uv, tint);
}

void TexView::Display(const LVector& center, const std::vector<LVector>& points, const std::vector<LVector>& uv,
					  LColor tint) const {
	if (points.size() < 3) return;
	if (points.size() != uv.size()) return;

	rlSetTexture(this->tex->id);

	// Texturing is only supported on RL_QUADS
	rlBegin(RL_QUADS);

	rlColor4ub(tint.r, tint.g, tint.b, tint.a);

	for (uint i = 0; i < points.size(); i++) {
		uint j = (i + 1) % points.size();

		rlTexCoord2f(this->uvCenter.x, this->uvCenter.y);
		rlVertex2f(center.x, center.y);

		rlTexCoord2f(uv[i].x, uv[i].y);
		rlVertex2f(points[i].x + center.x, points[i].y + center.y);

		rlTexCoord2f(uv[j].x, uv[j].y);
		rlVertex2f(points[j].x + center.x, points[j].y + center.y);

		rlTexCoord2f(uv[j].x, uv[j].y);
		rlVertex2f(points[j].x + center.x, points[j].y + center.y);
	}

	rlEnd();

	rlSetTexture(0);
}
