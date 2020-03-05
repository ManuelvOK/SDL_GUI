#pragma once

#include "position.h"

namespace SDL_GUI {
class Scrollable {
    int scroll_position_x_min();
    int scroll_position_x_max();
    int scroll_position_y_min();
    int scroll_position_y_max();
protected:
    Position _scroll_position;
    Position _overscroll;
    Position _underscroll;
    Position _child_overflow;

    bool _scrolling_x_enabled = false;
    bool _scrolling_y_enabled = false;

    Scrollable() = default;
public:
    Position scroll_position() const;

    void set_scroll_position(Position offset);

    void set_scroll_position_x(int x);
    void set_scroll_position_y(int y);

    void scroll_left(int value = 10);
    void scroll_right(int value = 10);
    void scroll_up(int value = 10);
    void scroll_down(int value = 10);

    void enable_scrolling();
    void disable_scrolling();

    void enable_scrolling_x();
    void disable_scrolling_x();

    void enable_scrolling_y();
    void disable_scrolling_y();

    void set_overscroll_x(int x);
    void set_underscroll_x(int x);
    void set_overscroll_y(int y);
    void set_underscroll_y(int y);
};
}
