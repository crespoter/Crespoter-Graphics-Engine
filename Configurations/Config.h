#pragma once
#include <string>
#include "Engine/Window/WindowInterface.h"

// TODO: read from a config file instead

namespace ENGINE_CONFIG
{
	const static inline std::string WINDOW_NAME = "Crespoter Game Engine";
	const static inline IWindowInterface::WINDOW_MODE WINDOW_MODE = IWindowInterface::WINDOW_MODE::WINDOWED;
}