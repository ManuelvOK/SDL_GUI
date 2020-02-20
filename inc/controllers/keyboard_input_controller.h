#pragma once

#include <SDL2/SDL.h>

#include "controller_base.h"
#include "../models/keyboard_input_model.h"

namespace SDL_GUI {
class KeyboardInputController : public ControllerBase {
protected:
    KeyboardInputModel *_keyboard_input_model = nullptr;

    virtual void handle_key_press(SDL_KeyboardEvent kb_event);

    virtual void handle_key_release(SDL_KeyboardEvent kb_event);

    bool *_is_running;
public:

    KeyboardInputController(bool *is_running) : _is_running(is_running) {}

    virtual void set_model(KeyboardInputModel *input_model) {
        this->_keyboard_input_model = input_model;
    }
    virtual void update() override;
};
}
