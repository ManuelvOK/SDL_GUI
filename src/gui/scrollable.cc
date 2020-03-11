#include <gui/scrollable.h>

#include <algorithm>

using namespace SDL_GUI;

void Scrollable::reposition() {
    this->set_scroll_position(this->_scroll_position);
}

int Scrollable::scroll_position_x_max() {
    return this->_underscroll._x;
}

int Scrollable::scroll_position_x_min() {
    return this->_child_overflow._x - this->_overscroll._x;
}

int Scrollable::scroll_position_y_max() {
    return this->_underscroll._y;
}

int Scrollable::scroll_position_y_min() {
    return this->_child_overflow._y - this->_overscroll._y;
}

Position Scrollable::scroll_position() const {
    return this->_scroll_position;
}

void Scrollable::set_scroll_position(Position offset) {
    this->set_scroll_position_x(offset._x);
    this->set_scroll_position_y(offset._y);
}

void Scrollable::set_scroll_position_x(int x) {
    if (this->_scrolling_x_enabled) {
        this->_scroll_position._x = std::max(this->scroll_position_x_min(), std::min(this->scroll_position_y_max(), x));
    }
}

void Scrollable::set_scroll_position_y(int y) {
    if (this->_scrolling_y_enabled) {
        this->_scroll_position._y = y;
    }
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

void Scrollable::set_underscroll_x(int x) {
    this->_underscroll._x = x;
}

void Scrollable::set_overscroll_x(int x) {
    this->_overscroll._x = x;
}

void Scrollable::set_underscroll_y(int y) {
    this->_underscroll._y = y;
}

void Scrollable::set_overscroll_y(int y) {
    this->_overscroll._y = y;
}

