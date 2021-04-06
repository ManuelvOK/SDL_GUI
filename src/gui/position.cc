#include <gui/position.h>

using namespace SDL_GUI;

Position Position::operator+(const Position &p) const {
    return Position(this->_x + p._x, this->_y + p._y);
}

Position Position::operator-(const Position &p) const {
    return Position(this->_x - p._x, this->_y - p._y);
}

Position & Position::operator+=(const Position &p) {
    *this = *this + p;
    return *this;
}

Position & Position::operator-=(const Position &p) {
    *this = *this - p;
    return *this;
}

std::ostream& SDL_GUI::operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos._x << "|" << pos._y << ")";
    return os;
}
