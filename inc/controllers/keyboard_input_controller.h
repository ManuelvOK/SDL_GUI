#pragma once

#include <SDL2/SDL.h>

#include "controller_base.h"
#include "../models/keyboard_input_model.h"

namespace SDL_GUI {
class KeyboardInputController : public ControllerBase {
    KeyboardInputModel *_input_model = nullptr;

    void handle_key_press(SDL_KeyboardEvent kb_event);

    bool *_is_running;
public:

    KeyboardInputController(bool *is_running) : _is_running(is_running) {}

    virtual void set_model(KeyboardInputModel *input_model) {
        this->_input_model = input_model;
    }
    virtual void update() override;
};
}
