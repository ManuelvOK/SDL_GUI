#pragma once

#include <map>
#include <set>

#include <SDL2/SDL.h>

#include "model_base.h"
#include "../gui/position.h"

namespace SDL_GUI {
/**
 *
 */
class InputModelBase : public ModelBase {
protected:
    Position _mouse_position;   /**< current position of the mouse */
    Position _mouse_offset;     /**< difference between current and previous mouse position */

    Position _mouse_wheel;      /**< mouse wheel difference */
public:

    /**
     * Reset mouse wheel difference
     */
    void update();

    /**
     * Setter for the mouse position.
     * This will also change the mouse offset.
     * @param position current position of the mouse
     */
    void set_mouse_position(Position position);

    /**
     * getter for _mouse_position
     * @returns this->_mouse_position
     */
    Position mouse_position() const;

    /**
     * getter for _mouse_offset
     * @returns this->_mouse_offset
     */
    Position mouse_offset() const;

    /**
     * Setter for the mouse wheel change
     * @param offset mouse wheel change
     */
    void set_mouse_wheel(Position offset);

    /**
     * getter for _mouse_wheel
     * @returns this->_mouse_wheel
     */
    Position mouse_wheel() const;

};

template<typename T>
class InputModel : public InputModelBase {
    static_assert(std::is_enum<T>::value);

    std::set<T> _pressed;   /**< active (pressed) inputs */
    std::set<T> _down;      /**< inputs that just got activated (pressed) */
    std::set<T> _up;        /**< inputs that just got deactivated (released) */


public:
    /**
     * Constructor
     */
    InputModel() = default;

    /**
     * Clear _down and _up
     */
    void update() {
        InputModelBase::update();
        this->_down.clear();
        this->_up.clear();
    }

    /**
     * set the state of a given input to be pressed
     * @param input The input to set as pressed
     */
    void press(T input) {
        this->_down.insert(input);
        this->_pressed.insert(input);
    }

    /**
     * Set the state of a given input to be pressed just for this one tick.
     * This is used for events that will not get released.
     * @param input The input to trigger
     */
    void trigger(T input) {
        this->_down.insert(input);
    }

    /**
     * set the state of a given input to be released
     * @param input The input to set as released
     */
    void release(T input) {
        this->_pressed.erase(input);
        this->_up.insert(input);
    }

    /**
     * check if a given key is pressed
     * @param key the key to check
     * @returns True if key is pressed. False otherwise
     */
    bool is_pressed(T key) const {
        return this->_pressed.contains(key);
    }

    /**
     * check if a given key has just been pressed
     * @param key the key to check
     * @returns True if key has pressed down. False otherwise
     */
    bool is_down(T key) const {
        return this->_down.contains(key);
    }

    /**
     * check if a given key has just been released
     * @param key the key to check
     * @returns True if key has just been released. False otherwise
     */
    bool is_up(T key) const {
        return this->_up.contains(key);
    }
};
}
