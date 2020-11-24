#pragma once

#include <iostream>

namespace SDL_GUI {
/** 2 dimensional point */
class Position {
public:
    int _x = 0; /**< horizontal position */
    int _y = 0; /**< vertical position */

    /** Default constructor */
    Position() = default;

    /**
     * Constructor
     * @param x horizontal position
     * @param y vertical position
     */
    Position(int x, int y) : _x(x), _y(y) {}

    /**
     * memberwise addition of two Positions
     * @param p position to add
     * @return this + p
     */
    Position operator+(const Position &p);

    /**
     * memberwise substraction of two Positions
     * @param p position to substract
     * @return this - p
     */
    Position operator-(const Position &p);

    /**
     * Unary Addition
     * @param p position to add
     * @return this + p
     */
    Position & operator+=(const Position &p);

    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
};

/**
 * Print out the coordinates of this.
 * @param os out stream
 * @param pos position to output
 * @return output stream
 */
std::ostream& operator<<(std::ostream& os, const Position& pos);
}
