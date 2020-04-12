#pragma once

#include "position.h"

/**
 * Objects consisting out of a position, width and height
 */
namespace SDL_GUI {
class Positionable {
protected:
    Position _position;             /**< objects position */
    unsigned _width = 0;            /**< objects width */
    unsigned _height = 0;           /**< objects height */

    Position _absolute_position;    /**< absolute position in window */

    /**
     * Constructor
     * Position (0,0), width 0, height 0
     */
    Positionable() : _position(), _absolute_position() {}

    /**
     * Constructor
     * @param position position
     */
    Positionable(Position position) : _position(position), _absolute_position() {}
public:
    /**
     * Setter for _position
     * @param position position to set
     */
    void set_position(Position position);

    /**
     * Offset position.
     * @param position Position to add to current position
     */
    void move(Position position);

    /**
     * setter for _x
     * @param x x coordinate of position
     */
    void set_x(int x);

    /**
     * setter for _y
     * @param y y coordinate of position
     */
    void set_y(int y);

    /**
     * setter for _width
     * @param width width to set
     */
    void set_width(unsigned width);

    /**
     * setter for _height
     * @param height height to set
     */
    void set_height(unsigned height);

    /**
     * getter for _position
     * @returns position of object
     */
    Position position() const;

    /**
     * getter for _position._x
     * @returns x coordinate of position
     */
    int x() const;

    /**
     * getter for _position._y
     * @returns y coordinate of position
     */
    int y() const;

    /**
     * getter for _width
     * @returns width of object
     */
    unsigned width() const;

    /**
     * getter for _height
     * @returns height of object
     */
    unsigned height() const;

};
}
