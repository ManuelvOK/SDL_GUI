#pragma once

#include <map>

#include <SDL2/SDL.h>

#include "../input_keys.h"

namespace SDL_GUI {
/** config for keyboard inputs */
const std::map<SDL_Scancode, InputKey> keyboard_input_config;

/** config for window events */
const std::map<SDL_WindowEventID, InputKey> window_event_config;

/** config for mouse input */
const std::map<Uint8, InputKey> mouse_input_config;
}

