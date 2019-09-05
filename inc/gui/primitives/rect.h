#pragma once

#include <gui/drawable.h>
#include <gui/rgb.h>

class Rect : public Drawable {
    RGB _color; /**< background color */
    RGB _border_color; /**< border color */
    bool _border = false; /**< border flag */

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

    void set_color(RGB color);

    void draw(SDL_Renderer *renderer, Position position) const override;
};
