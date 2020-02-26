#include <gui/positionable.h>

using namespace SDL_GUI;

void Positionable::set_position(Position position) {
    this->_position = position;
}

void Positionable::set_x(int x) {
    this->_position._x = x;
}

void Positionable::set_y(int y) {
    this->_position._y = y;
}

void Positionable::set_width(unsigned width) {
    this->_width = width;
}

void Positionable::set_height(unsigned height) {
    this->_height = height;
}

unsigned Positionable::height() const {
    return this->_height;
}

unsigned Positionable::width() const {
    return this->_width;
}

Position Positionable::position() const {
    return this->_position;
}
