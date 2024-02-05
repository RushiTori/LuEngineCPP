#ifndef LALIGNS_HPP
#define LALIGNS_HPP

#include "EngineUtils.hpp"

namespace LAligns {

using type = uint8_t;

constexpr type TOP = 0;
constexpr type LEFT = 0;

constexpr type CENTER = 1;

constexpr type BOTTOM = 2;
constexpr type RIGHT = 2;

inline LVector AlignedOffset(const LVector& sizes, type alignX, type alignY) {
	return -sizes / 2 * LVector(alignX, alignY);
}

}  // namespace LAligns

#endif	// LALIGNS_HPP
