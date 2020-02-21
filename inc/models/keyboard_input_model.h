#pragma once

#include <map>
#include <set>

#include <SDL2/SDL.h>

#include "model_base.h"

namespace SDL_GUI {
template<typename T>
class KeyboardInputModel : public ModelBase {
    static_assert(std::is_enum<T>::value);

    std::set<T> _pressed;
    std::set<T> _down;
    std::set<T> _up;

public:
    KeyboardInputModel() = default;

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
