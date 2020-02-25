#include <gui/scrollable.h>

using namespace SDL_GUI;

Position Scrollable::scroll_position() const {
    return this->_scroll_position;
}

void Scrollable::set_scroll_position(Position offset) {
    this->_scroll_position = offset;
}

void Scrollable::set_scroll_position_x(int x) {
    this->_scroll_position._x = x;
}

void Scrollable::set_scroll_position_y(int y) {
    this->_scroll_position._y = y;
}

void Scrollable::lock_scrolling_x() {
    this->_scroll_min._x = 0;
    this->_scroll_max._x = 0;
}

void Scrollable::lock_scrolling_y() {
    this->_scroll_min._y = 0;
    this->_scroll_max._y = 0;
}

void Scrollable::set_scroll_range_min_x(int x) {
    this->_scroll_min._x = x;
}

void Scrollable::set_scroll_range_max_x(int x) {
    this->_scroll_max._x = x;
}

void Scrollable::set_scroll_range_min_y(int y) {
    this->_scroll_min._y = y;
}

void Scrollable::set_scroll_range_max_y(int y) {
    this->_scroll_max._y = y;
}

