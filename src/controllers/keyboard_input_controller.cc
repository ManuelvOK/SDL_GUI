#include <controllers/keyboard_input_controller.h>

using namespace SDL_GUI;

void KeyboardInputController::update() {
    SDL_Event event;
    while (0 != SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: this->handle_key_press(event.key);
                              break;
            default: break;
        }
    }
}

void KeyboardInputController::handle_key_press(SDL_KeyboardEvent kb_event) {
    switch (kb_event.keysym.scancode) {
        case SDL_SCANCODE_Q:
        case SDL_SCANCODE_ESCAPE: this->_input_model->set_pressed(KeyboardInputModel::Key::QUIT);
                                  *this->_is_running = false;
                                  break;
        default: break;
    }
}
