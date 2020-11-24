#pragma once

#include "../drawable.h"
#include "../rgb.h"

namespace SDL_GUI {
/** primitive for drawing a rectangle */
class Rect : public Drawable {
public:
    /**
     * Constructor
     * @param parent_position absolute position of parent
     * @param position local position inside parent drawable
     * @param width width of rect
     * @param height height of rect
     */
    Rect(Position parent_position = {0, 0}, Position position = {0, 0}, unsigned width = 0,
         unsigned height = 0);

    void draw(SDL_Renderer *renderer, Position position) const override;
};
}
