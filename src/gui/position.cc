#include <gui/position.h>

using namespace SDL_GUI;

std::ostream& SDL_GUI::operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos._x << "|" << pos._y << ")";
    return os;
}
