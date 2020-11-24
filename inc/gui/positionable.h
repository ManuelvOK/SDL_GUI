#pragma once

#include "position.h"

namespace SDL_GUI {
/** Objects consisting out of a position (relative and absolute), width and height */
class Positionable {
protected:
    Position _position;             /**< objects position relative to parent */
    Position _absolute_position;    /**< objects absolute position in window */
    unsigned _width = 0;            /**< objects width */
    unsigned _height = 0;           /**< objects height */

    /** Default constructor */
    Positionable() = default;
public:
    /**
     * Constructor
     * @param position position relative to parent
     * @param absolute_position position in window
     */
    Positionable(Position position, Position absolute_position = {0,0})
        : _position(position), _absolute_position(absolute_position) {}

    /**
     * Setter for _position
     * This also changes _absolute_position.
     * @param position position to set
     */
    void set_position(Position position);

    /**
     * Setter for _absolute_position
     * @param position position to set
     */
    void set_absolute_position(Position position);

    /**
     * Offset position.
     * This also moves the absolute position
     * @param position Position to add to current position
     */
    virtual void move(Position position);

    /**
     * Offset position.
     * @param position Position to add to current position
     */
    void move_absolute(Position position);

    /**
     * setter for _position._x
     * This also changes _absolute_position._x
     * @param x x coordinate of position
     */
    void set_x(int x);

    /**
     * setter for _absolute_position._x
     * @param x x coordinate of position
     */
    void set_absolute_x(int x);

    /**
     * setter for _position._y
     * This also changes _absolute_position._y
     * @param y y coordinate of position
     */
    void set_y(int y);

    /**
     * setter for _absolute_position._y
     * @param y y coordinate of position
     */
    void set_absolute_y(int y);

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
     * getter for _absolute_position
     * @returns absolute position of object
     */
    Position absolute_position() const;

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
    virtual unsigned width() const;

    /**
     * getter for _height
     * @returns height of object
     */
    virtual unsigned height() const;

    /**
     * check if Position is inside this
     * @param position Position to check for
     * @returns True if position is inside. False otherwise.
     */
    virtual bool is_inside(Position position) const;
};
}
