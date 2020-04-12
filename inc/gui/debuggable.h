#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

#include "position.h"

namespace SDL_GUI {
class Drawable;
class Debuggable {
protected:
    bool _debug_information_initialised = false;
    bool _debug_information_shown = false;

    std::vector<Drawable *> _debug_information;

    std::function<void (SDL_Renderer *, Position)> _draw_debug_information;

    void default_draw_debug_information(SDL_Renderer *renderer, Position position) const;

    Debuggable();
public:
    ~Debuggable();

    void draw_debug_information(SDL_Renderer *renderer, Position position) const;

    void set_debug_information_shown(bool debug_information_shown);

    void show_debug_information();

    void hide_debug_information();

};
}
