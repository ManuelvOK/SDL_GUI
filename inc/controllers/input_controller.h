#pragma once

#include <SDL2/SDL.h>

#include <controllers/controller_base.h>
#include <models/input_model.h>

class InputController : public ControllerBase {
    InputModel *_input_model = nullptr;

    void handle_key_press(SDL_KeyboardEvent kb_event);
public:
    virtual void set_model(InputModel *input_model) {
        this->_input_model = input_model;
    }
    virtual void update() override;
};
