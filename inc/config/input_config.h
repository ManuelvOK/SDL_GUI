#pragma once

#include <map>
#include <set>

#include <SDL2/SDL.h>

namespace SDL_GUI {
/**
 * This enum holds all the inputs that are possible. Those are used in the input model and mapped in
 * the input config
 */
enum class InputKey {QUIT};

/**
 * This enum holds all the input states the application can be in.
 */
enum class InputState {ALL};

/** config for keyboard inputs */
const std::map<InputState, std::map<std::set<SDL_Scancode>, std::map<SDL_Scancode, InputKey>>> keyboard_input_config;

/** config for window events */
const std::map<SDL_WindowEventID, InputKey> window_event_config;

/** config for mouse input */
const std::map<InputState, std::map<std::set<SDL_Scancode>, std::map<Uint8, InputKey>>> mouse_input_config;
}

