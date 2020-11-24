#pragma once

#include "../drawable.h"

namespace SDL_GUI {
/** primitive for drawing a vertical line */
class VerticalLine : public Drawable {
public:
    /** Constructor */
    VerticalLine() : Drawable("VerticalLine") {}

    void draw(SDL_Renderer *renderer, Position position) const override;
};
}
