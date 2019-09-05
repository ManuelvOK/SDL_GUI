#pragma once

#include <array>

#include <models/model_base.h>
#include <gui/position.h>

class MouseInputModel : public ModelBase {
    std::array<bool, 2> _current_states;
    Position _current_position;
public:
    enum class Button {
        LEFTCLICK,
        RIGHTCLICK,
    };
    void update();

    void set_pressed(Button button);
    bool is_pressed(Button button) const;

    void set_position(Position position);
    Position current_position() const;

};

