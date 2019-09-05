#pragma once

#include <array>

#include <models/model_base.h>

class KeyboardInputModel : public ModelBase {
    std::array<bool, 1> _current_states;
public:
    enum class Key {
        QUIT,
    };

    void update();
    void set_pressed(Key key);

    bool is_pressed(Key key) const;
};
