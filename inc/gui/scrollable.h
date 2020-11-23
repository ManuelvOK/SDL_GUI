#pragma once

#include "position.h"

namespace SDL_GUI {
/**
 * Abstract class for objects that can be scrolled.
 * TODO: This should have some kind of bounds checking on the actual scrolling.
 */
class Scrollable {
protected:
    Position _scroll_position;  /**< current offset from the original position */

    /** flag describing whether scrolling on x axis is enabled */
    bool _scrolling_x_enabled = false;
    /** flag describing whether scrolling on y axis is enabled */
    bool _scrolling_y_enabled = false;

    /** Constructor */
    Scrollable() = default;
public:
    /**
     * Getter for _scroll_position
     * @return  this->_scroll_position
     */
    Position scroll_position() const;

    /**
     * Setter for _scroll_position
     * @param offset position to set _scroll_position to
     */
    void set_scroll_position(Position offset);

    /**
     * Setter for the x value of _scroll_position
     * @param x x value of _scroll_position
     */
    void set_scroll_position_x(int x);

    /**
     * Setter for the y value of _scroll_position
     * @param y y value of _scroll_position
     */
    void set_scroll_position_y(int y);

    /**
     * decrease x coordinate of scroll position
     * @param value value
     */
    void scroll_left(int value = 10);

    /**
     * increase x coordinate of scroll position
     * @param value value
     */
    void scroll_right(int value = 10);

    /**
     * decrease y coordinate of scroll position
     * @param value value
     */
    void scroll_up(int value = 10);

    /**
     * increase y coordinate of scroll position
     * @param value value
     */
    void scroll_down(int value = 10);

    /** enable scrolling in x and y direction */
    void enable_scrolling();

    /** disable scrolling in x and y direction */
    void disable_scrolling();

    /** enable scrolling in x direction */
    void enable_scrolling_x();

    /** disable scrolling in x direction */
    void disable_scrolling_x();

    /** enable scrolling in y direction */
    void enable_scrolling_y();

    /** disable scrolling in x direction */
    void disable_scrolling_y();
};
}
