#pragma once

#include <map>

#include <SDL2/SDL.h>

#include "../input_keys.h"

namespace SDL_GUI {
const std::map<SDL_Scancode, InputKey> input_config = {
    {SDL_SCANCODE_Q, InputKey::QUIT},
    {SDL_SCANCODE_ESCAPE, InputKey::QUIT},
};
}
