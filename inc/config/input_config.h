#pragma once

#include <map>

#include <SDL2/SDL.h>

#include "../input_keys.h"

namespace SDL_GUI {
const std::map<SDL_Scancode, InputKey> keyboard_input_config;

const std::map<SDL_WindowEventID, InputKey> window_event_config;

const std::map<Uint8, InputKey> mouse_input_config;
}

