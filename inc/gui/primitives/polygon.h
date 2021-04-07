#pragma once

#include <list>

#include "../drawable.h"

namespace SDL_GUI {
class Polygon : public Drawable {
    std::list<Position> _points;

    unsigned _line_width = 1;

    virtual Drawable *clone() const override;
public:
    Polygon()
        :Drawable("Polygon") {}

    void add_point(Position point);

    void remove_point(Position &point);

    void remove_last_point();

    void set_line_width(unsigned width);

    void draw(SDL_Renderer *renderer, Position position) const override;
};
}
