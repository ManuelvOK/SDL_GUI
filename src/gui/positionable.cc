#include <gui/positionable.h>

using namespace SDL_GUI;

void Positionable::set_position(Position position) {
    this->_position = position;
}

void Positionable::move(Position position) {
    this->_position += position;
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

Position Positionable::position() const {
    return this->_position;
}

int Positionable::x() const {
    return this->_position._x;
}

int Positionable::y() const {
    return this->_position._y;
}

unsigned Positionable::width() const {
    return this->_width;
}

unsigned Positionable::height() const {
    return this->_height;
}

