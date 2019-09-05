#pragma once

#include <array>

#include <models/model_base.h>

class InputModel : public ModelBase {
    std::array<bool, 8> _current_states;
public:
    enum class InputKey {
        QUIT,
    };

    void update();
    void set_pressed(InputKey key);

    bool is_pressed(InputKey key) const;
};
