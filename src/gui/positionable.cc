#include <gui/positionable.h>

void Positionable::set_position(Position position) {
    this->_position = position;
}

void Positionable::set_width(unsigned width) {
    this->_width = width;
}

void Positionable::set_height(unsigned height) {
    this->_height = height;
}
