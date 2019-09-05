#pragma once

#include <gui/position.h>

/**
 * Objects consisting out of a position, width and height
 */
class Positionable {
protected:
    Position _position; /**< objects position */
    unsigned _width = 0; /**< objects width */
    unsigned _height = 0; /**< objects height */

    /**
     * Constructor
     * Position (0,0), width 0, height 0
     */
    Positionable() : _position() {}

    /**
     * Constructor
     *
     * @param position
     *   position
     */
    Positionable(Position position) : _position(position) {}
};
