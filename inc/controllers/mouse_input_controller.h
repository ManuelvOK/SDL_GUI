#pragma once

#include <SDL2/SDL.h>

#include "controller_base.h"
#include "../models/mouse_input_model.h"

namespace SDL_GUI {
class MouseInputController : public ControllerBase {
    /**
     * Model for mouse input
     */
    MouseInputModel *_input_model = nullptr;

    /**
     * change state of mouse input model based on the given inputs
     * @param mouse_event The mouse event SDL captures
     */
    void handle_button_press(SDL_MouseButtonEvent mouse_event);
public:
    /**
     * set the mouse input model
     * @param input_model pointer to the model to set as mouse input model
     */
    virtual void set_model(MouseInputModel *input_model) {
        this->_input_model = input_model;
    }

    virtual void update() override;
};
}
