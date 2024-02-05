#ifndef ENGINE_MAIN_HPP
#define ENGINE_MAIN_HPP

#include "Assets.hpp"
#include "InputHandler.hpp"

void LuEngineSetup(const std::vector<std::string>& args, uint32_t width, uint32_t height, const std::string& projName,
				   uint32_t targetFPS, ConfigFlags flags = FLAG_WINDOW_ALWAYS_RUN);
void LuEngineUpdate();
void LuEngineDestroy();

#endif	// ENGINE_MAIN_HPP
