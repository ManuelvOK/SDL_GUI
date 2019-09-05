#include <controllers/mouse_input_controller.h>

void MouseInputController::update() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    this->_input_model->set_position({x, y});
    SDL_Event event;
    while (0 != SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_MOUSEBUTTONDOWN: this->handle_button_press(event.button);
                              break;
            default: break;
        }
    }
}

void MouseInputController::handle_button_press(SDL_MouseButtonEvent mouse_event) {
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: this->_input_model->set_pressed(MouseInputModel::Button::LEFTCLICK);
                              break;
        case SDL_BUTTON_RIGHT: this->_input_model->set_pressed(MouseInputModel::Button::RIGHTCLICK);
                               break;
        default: break;
    }
}
