#pragma once

#include <map>
#include <set>

#include <SDL2/SDL.h>

#include "model_base.h"
#include "../gui/position.h"

namespace SDL_GUI {

class InputModelBase : public ModelBase {
protected:
    /**
     * current position of the mouse
     */
    Position _current_position;
public:
    /**
     * set the position of the mouse pointer
     * @param position the Position to set the mouse pointer to
     */
    void set_position(Position position);

    /**
     * get the mouse pointers current position
     * @returns the mouse pointers current position:
     */
    Position current_position() const;
};

template<typename T>
class InputModel : public InputModelBase {
    static_assert(std::is_enum<T>::value);

    std::set<T> _pressed;
    std::set<T> _down;
    std::set<T> _up;

public:
    InputModel() = default;

    void update() {
        this->_down.clear();
        this->_up.clear();
    }

    /**
     * set the state of a given key to be pressed
     * @param key The key to set as pressed
     */
    void press(T key) {
        this->_down.insert(key);
        this->_pressed.insert(key);
    }

    /**
     * set the state of a given key to be released
     * @param key The key to set as released
     */
    void release(T key) {
        this->_pressed.erase(key);
        this->_up.insert(key);
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
