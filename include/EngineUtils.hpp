#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include <LuLib.hpp>

#include "LColor.hpp"
#include "LVector.hpp"
#include "WorldCamera.hpp"

inline uint64_t frameCount = 0;
inline WorldCamera globalCamera = WorldCamera(LVector(0, 0), 1);

inline LVector GetScreenSizes() { return LVector(GetScreenWidth(), GetScreenHeight()); }

#endif	// ENGINE_UTILS_HPP
