#pragma once

#include "../drawable.h"

namespace SDL_GUI {
class VerticalLine : public Drawable {
public:
    VerticalLine() = default;

    void draw(SDL_Renderer *renderer, Position position) const override;
};
}
