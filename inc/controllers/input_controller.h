#pragma once

#include <SDL2/SDL.h>

#include <map>

#include "controller_base.h"
#include "../models/input_model.h"

namespace SDL_GUI {

template<typename T>
class InputController : public ControllerBase {
    static_assert(std::is_enum<T>::value);

protected:
    InputModel<T> *_input_model = nullptr;

    std::map<SDL_Scancode, T> _keyboard_input_config;

    std::map<SDL_WindowEventID, T> _window_event_config;

    virtual void handle_key_press(SDL_KeyboardEvent kb_event) {
        if (kb_event.repeat) {
            return;
        }
        if (this->_keyboard_input_config.contains(kb_event.keysym.scancode)) {
            this->_input_model->press(this->_keyboard_input_config[kb_event.keysym.scancode]);
        }
    }

    virtual void handle_key_release(SDL_KeyboardEvent kb_event) {
        if (this->_keyboard_input_config.contains(kb_event.keysym.scancode)) {
            this->_input_model->release(this->_keyboard_input_config[kb_event.keysym.scancode]);
        }
    }

    virtual void handle_button_press(SDL_MouseButtonEvent mouse_event) {
        //TODO: implement
    }

    virtual void handle_button_release(SDL_MouseButtonEvent mouse_event) {
        //TODO: implement
    }

    virtual void handle_scrolling(SDL_MouseWheelEvent mouse_wheel_event) {
        //TODO: implement
    }

    virtual void handle_window_event(SDL_WindowEvent window_event) {
        SDL_WindowEventID event_id = static_cast<SDL_WindowEventID>(window_event.event);
        if (this->_window_event_config.contains(event_id)) {
            this->_input_model->press_once(this->_window_event_config[event_id]);
        }
    }

public:

    InputController(InputModel<T> *input_model, std::map<SDL_Scancode, T> keyboard_input_config, std::map<SDL_WindowEventID, T> window_event_config) : _input_model(input_model), _keyboard_input_config(keyboard_input_config), _window_event_config(window_event_config) {}

    virtual void update() override {
        this->_input_model->update();
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->_input_model->set_position({x, y});
        SDL_Event event;
        while (0 != SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    this->handle_key_press(event.key);
                    break;
                case SDL_KEYUP:
                    this->handle_key_release(event.key);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    this->handle_button_press(event.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    this->handle_button_release(event.button);
                    break;
                case SDL_MOUSEWHEEL:
                    this->handle_scrolling(event.wheel);
                    break;
                case SDL_WINDOWEVENT:
                    this->handle_window_event(event.window);
                    break;
                default:
                    break;
            }
        }
    }

};
}
