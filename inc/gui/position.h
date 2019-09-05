#pragma once

/**
 * 2 dimensional point
 */
class Position {
public:
    int _x = 0; /**< horizontal position */
    int _y = 0; /**< vertical position */

    /**
     * Constructor
     * Position (0,0)
     */
    Position() {}

    /**
     * Constructor
     *
     * @param x
     *   horizontal position
     * @param y
     *   vertical position
     */
    Position(int x, int y) : _x(x), _y(y) {}

    Position operator+(const Position &p) {
        return Position(this->_x + p._x, this->_y + p._y);
    }
};
