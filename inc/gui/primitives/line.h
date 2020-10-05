#pragma once

#include "../drawable.h"

namespace SDL_GUI {
class Line : public Drawable {
protected:
    Position &_begin = this->_position;
    Positionable _end;
public:

    Line(Position parent_position = {0,0}, Position begin = {0,0}, Position end = {0,0}) : Drawable("Line", parent_position, begin), _end(end, end - begin) {}

    void draw(SDL_Renderer *renderer, Position position) const override;

    void set_end_relative_to_begin(Position position);
    void set_end_relative_to_parent(Position position);
    void set_begin(Position position);

    const Position end_relative_to_begin() const;
    const Position end_relative_to_parent() const;
    const Position begin() const;
};
}
