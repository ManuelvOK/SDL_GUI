#pragma once

#include <array>

#include <models/model_base.h>
#include <gui/position.h>

class MouseInputModel : public ModelBase {
    /**
     * current state of the two Mouse buttons
     */
    std::array<bool, 2> _current_states;
    /**
     * current position of the mouse
     */
    Position _current_position;
public:
    enum class Button {
        LEFTCLICK,
        RIGHTCLICK,
    };
    void update();

    /**
     * set a mouse buttons state to be pressed
     * @param button The mouse button to set as pressed
     */
    void set_pressed(Button button);
    /**
     * get the state of a given Mouse button
     * @param button The mouse button to get the state of
     * @returns the State of the given mouse button
     */
    bool is_pressed(Button button) const;

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

