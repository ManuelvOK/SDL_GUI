#include <gui/positionable.h>

using namespace SDL_GUI;

void Positionable::set_position(Position position) {
    Position diff = position - this->_position;
    this->_position = position;
    this->_absolute_position += diff;
}

void Positionable::set_absolute_position(Position position) {
    this->_absolute_position = position;
}

void Positionable::move(Position position) {
    this->_position += position;
    this->_absolute_position += position;
}

void Positionable::move_absolute(Position position) {
    this->_absolute_position += position;
}

void Positionable::set_x(int x) {
    int diff = x - this->_position._x;
    this->_position._x = x;
    this->_absolute_position._x += diff;
}

void Positionable::set_absolute_x(int x) {
    this->_absolute_position._x = x;
}

void Positionable::set_y(int y) {
    int diff = y - this->_position._y;
    this->_position._y = y;
    this->_absolute_position._y += diff;
}

void Positionable::set_absolute_y(int y) {
    this->_absolute_position._y =y;
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

Position Positionable::absolute_position() const {
    return this->_absolute_position;
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


bool Positionable::is_inside(Position position) const {
    return position._x > this->_absolute_position._x &&
           position._y > this->_absolute_position._y &&
           position._x < this->_absolute_position._x + static_cast<int>(this->_width) &&
           position._y < this->_absolute_position._y + static_cast<int>(this->_height);
}
