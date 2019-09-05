#pragma once

#include <gui/drawable.h>
#include <gui/rgb.h>

class Rect : public Drawable {
public:
    /**
     * default Constructor
     */
    Rect() = default;

    /**
     * Constructor
     *
     * @param position
     *   local position inside parent drawable
     * @param width
     *   width of rect
     * @param height
     *   height of rect
     */
    Rect(Position position, unsigned width, unsigned height);

    void draw(SDL_Renderer *renderer, Position position) const override;
};
