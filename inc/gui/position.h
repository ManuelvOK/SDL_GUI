#pragma once

#include <iostream>

/**
 * 2 dimensional point
 */
namespace SDL_GUI {
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

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};

std::ostream& operator<<(std::ostream& os, const Position& pos);

}
