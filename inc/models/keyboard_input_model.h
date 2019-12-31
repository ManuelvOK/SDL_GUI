#pragma once

#include <array>

#include <models/model_base.h>

class KeyboardInputModel : public ModelBase {
    /**
     * Array stating the state of the different keys. For now it is pressed or not pressed
     */
    std::array<bool, 1> _current_states;
public:
    enum class Key {
        QUIT,
    };

    void update();
    /**
     * set the state of a given key to be pressed
     * @param key The key to set as pressed
     */
    void set_pressed(Key key);

    /**
     * get the state of a key
     * @param key the key to get the state of
     * @returns the state of the given key
     */
    bool is_pressed(Key key) const;
};
