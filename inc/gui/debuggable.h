#pragma once

#include <functional>
#include <vector>

#include <SDL2/SDL.h>

#include "position.h"

namespace SDL_GUI {
class Drawable;
/** Abstract class for Objects that do have debugging information to draw. */
class Debuggable {
protected:
    /** Flag that determines whether the debug information has already been initialised */
    bool _debug_information_initialised = false;

    /** Flag that determines whether the debug information should be rendered */
    bool _debug_information_shown = false;

    /** Drawables to draw as debug information */
    std::vector<Drawable *> _debug_information;

    /** function to call for drawing debug information */
    std::function<void (SDL_Renderer *, Position)> _draw_debug_information;

    /** default function to call for drawing debug information */
    void default_draw_debug_information(SDL_Renderer *renderer, Position position) const;

    /** Constructor */
    Debuggable();
public:
    /** Destructor */
    ~Debuggable();

    /**
     * Draw the drawables that represent the debug informaiton
     * @param renderer the aplications renderer
     * @param position absolute position to draw debug information
     */
    void draw_debug_information(SDL_Renderer *renderer, Position position) const;

    /**
     * Setter for _debug_information_shown
     * @param debug_information_shown value
     */
    void set_debug_information_shown(bool debug_information_shown);

    /** Set _debug_information_shown to true */
    void show_debug_information();

    /** Set _debug_information_shown to false */
    void hide_debug_information();
};
}
