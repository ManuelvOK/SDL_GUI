#pragma once

#include <SDL2/SDL.h>

#include <controllers/controller_base.h>
#include <models/mouse_input_model.h>

class MouseInputController : public ControllerBase {
    MouseInputModel *_input_model = nullptr;

    void handle_button_press(SDL_MouseButtonEvent mouse_event);
public:
    virtual void set_model(MouseInputModel *input_model) {
        this->_input_model = input_model;
    }
    virtual void update() override;
};
