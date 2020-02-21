#pragma once

#include <SDL2/SDL.h>

#include <map>

#include "controller_base.h"
#include "../models/keyboard_input_model.h"

namespace SDL_GUI {

enum class Key {
    QUIT,
};

template<typename T>
class KeyboardInputController : public ControllerBase {
    static_assert(std::is_enum<T>::value);

protected:
    KeyboardInputModel<T> *_keyboard_input_model = nullptr;

    std::map<SDL_Scancode, T> _input_config;

    virtual void handle_key_press(SDL_KeyboardEvent kb_event) {
        if (this->_input_config.contains(kb_event.keysym.scancode)) {
            this->_keyboard_input_model->press(this->_input_config[kb_event.keysym.scancode]);
        }
    }

    virtual void handle_key_release(SDL_KeyboardEvent kb_event) {
        if (this->_input_config.contains(kb_event.keysym.scancode)) {
            this->_keyboard_input_model->release(this->_input_config[kb_event.keysym.scancode]);
        }
    }

public:

    KeyboardInputController(KeyboardInputModel<T> *keyboard_input_model, std::map<SDL_Scancode, T> input_config) : _keyboard_input_model(keyboard_input_model), _input_config(input_config) {}

    virtual void update() override {
        SDL_Event event;
        while (0 != SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN: this->handle_key_press(event.key);
                                  break;
                case SDL_KEYUP: this->handle_key_release(event.key);
                default: break;
            }
        }
    }

};
}
