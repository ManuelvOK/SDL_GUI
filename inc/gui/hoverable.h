#pragma once

#include "position.h"

namespace SDL_GUI {
class Hoverable {
protected:
    Position _relative_mouse_position;  /**< mouse position inside of this object */
    bool _mouse_is_inside = false;      /**< flag that determines whether the mouse is inside this object */
    int _hover_distance = -1;           /**< integer stating how many drawables are between this object and the mouse. -1 if the mouse is not inside this object */

    Hoverable() : _relative_mouse_position() {}
public:
    /**
     * setter for _relative_mouse_position
     * @param relative_mouse_position mouse position relative to this object
     */
    void set_relative_mouse_position(Position relative_mouse_position);

    /**
     * setter for _mouse_is_inside
     * @param mouse_is_inside value to set _mouse_is_inside to
     */
    void set_mouse_is_inside(bool mouse_is_inside);

    /**
     * setter for _hover_distance
     * @param hover_distance value to set _hover_distance to
     */
    void set_hover_distance(int hover_distance);

    /**
     * getter for _relative_mouse_position
     * @returns position of mouse relative to this object
     */
    Position relative_mouse_position() const;

    /**
     * getter for _mouse_is_inside
     * @returns True if The mouse posiiton is inside this object. False otherwise.
     */
    bool mouse_is_inside() const;

    /**
     * getter for _hover_distance
     * @returns number of objects between this and the mouse. -1 if mouse is not inside this.
     */
    int hover_distance() const;

};
}