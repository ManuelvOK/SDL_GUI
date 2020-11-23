#include <gui/scrollable.h>

#include <algorithm>

using namespace SDL_GUI;

Position Scrollable::scroll_position() const {
    return this->_scroll_position;
}

void Scrollable::set_scroll_position(Position offset) {
    this->set_scroll_position_x(offset._x);
    this->set_scroll_position_y(offset._y);
}

void Scrollable::set_scroll_position_x(int x) {
    if (this->_scrolling_x_enabled) {
        this->_scroll_position._x = x;
    }
}

void Scrollable::set_scroll_position_y(int y) {
    if (this->_scrolling_y_enabled) {
        this->_scroll_position._y = y;
    }
}

void Scrollable::scroll_left(int value) {
    this->set_scroll_position_x(this->_scroll_position._x - value);
}

void Scrollable::scroll_right(int value) {
    this->set_scroll_position_x(this->_scroll_position._x + value);
}

void Scrollable::scroll_up(int value) {
    this->set_scroll_position_y(this->_scroll_position._y - value);
}

void Scrollable::scroll_down(int value) {
    this->set_scroll_position_y(this->_scroll_position._y + value);
}

void Scrollable::enable_scrolling() {
    this->_scrolling_x_enabled = true;
    this->_scrolling_y_enabled = true;
}

void Scrollable::disable_scrolling() {
    this->_scrolling_x_enabled = false;
    this->_scrolling_y_enabled = false;
}

void Scrollable::enable_scrolling_x() {
    this->_scrolling_x_enabled = true;
}

void Scrollable::disable_scrolling_x() {
    this->_scrolling_x_enabled = false;
}

void Scrollable::enable_scrolling_y() {
    this->_scrolling_y_enabled = true;
}

void Scrollable::disable_scrolling_y() {
    this->_scrolling_y_enabled = false;
}

