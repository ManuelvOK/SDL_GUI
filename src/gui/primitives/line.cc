#include <gui/primitives/line.h>

using namespace SDL_GUI;

Drawable *Line::clone() const {
    return new Line(*this);
}

void Line::draw(SDL_Renderer *renderer, Position position) const {
    this->_style._color.activate(renderer);
    SDL_RenderDrawLine(renderer, position._x, position._y,
                       position._x + this->_end.x(),
                       position._y + this->_end.y());
}

void Line::set_end_relative_to_parent(Position position) {
    this->_end.set_absolute_position(position);
}

void Line::set_end_relative_to_begin(Position position) {
    this->_end.set_position(position);
}

void Line::set_begin(Position position) {
    this->set_position(position);
    this->_end.set_absolute_position(position + this->_end.position());
}

const Position Line::end_relative_to_begin() const {
    return this->_end.position();
}

const Position Line::end_relative_to_parent() const {
    return this->_end.absolute_position();
}

const Position Line::begin() const {
    return this->_begin;
}
