#pragma once

#include "position.h"

namespace SDL_GUI {
class Scrollable {
protected:
    Position _scroll_position;
    Position _scroll_min;
    Position _scroll_max;

    Scrollable() = default;
public:
    Position scroll_position() const;

    void set_scroll_position(Position offset);

    void set_scroll_position_x(int x);
    void set_scroll_position_y(int y);

    void lock_scrolling_x();
    void lock_scrolling_y();

    void set_scroll_range_min_x(int x);
    void set_scroll_range_max_x(int x);
    void set_scroll_range_min_y(int y);
    void set_scroll_range_max_y(int y);
};
}
