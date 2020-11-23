#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <vector>

#include "controller_base.h"
#include "../models/input_model.h"

namespace SDL_GUI {

/**
 * Read input and put all the events into a vector that can be accessed with `events()`.
 * The `SDL_PollEvent()` function deletes the returned events from the event queue. To be able to
 * process all the events with every registered input controller they have to be put into a vector.
 */
void read_sdl_events();

/**
 * Clear event vector.
 */
void clear_sdl_events();


/**
 * Getter for the events vector.
 * @return the events vector
 */
const std::vector<SDL_Event> events();

/**
 * This controller handles the mouse and keyboard input and changes on the window. These events get
 * propagated to the given input model.
 * @tparam T the applications Input Keys Enum
 */
template<typename T>
class InputController : public ControllerBase {
    static_assert(std::is_enum<T>::value);

protected:
    /** the applications input model */
    InputModel<T> *_input_model = nullptr;

    /** the applications keyboard input config */
    std::map<SDL_Scancode, T> _keyboard_input_config;

    /** the applications window event config */
    std::map<SDL_WindowEventID, T> _window_event_config;

    /** the applications mouse input config */
    std::map<Uint8, T> _mouse_input_config;


    /**
     * propagate key press to input model
     * @param kb_event event to propagate
     */
    virtual void handle_key_press(SDL_KeyboardEvent kb_event) {
        if (kb_event.repeat) {
            return;
        }
        if (this->_keyboard_input_config.contains(kb_event.keysym.scancode)) {
            this->_input_model->press(this->_keyboard_input_config[kb_event.keysym.scancode]);
        }
    }

    /**
     * propagate key release to input model
     * @param kb_event event to propagate
     */
    virtual void handle_key_release(SDL_KeyboardEvent kb_event) {
        if (this->_keyboard_input_config.contains(kb_event.keysym.scancode)) {
            this->_input_model->release(this->_keyboard_input_config[kb_event.keysym.scancode]);
        }
    }

    /**
     * propagate mouse button press to input model
     * @param mouse_event event to propagate
     */
    virtual void handle_button_press(SDL_MouseButtonEvent mouse_event) {
        if (this->_mouse_input_config.contains(mouse_event.button)) {
            this->_input_model->press(this->_mouse_input_config[mouse_event.button]);
        }
    }

    /**
     * propagate mouse button release to input model
     * @param mouse_event event to propagate
     */
    virtual void handle_button_release(SDL_MouseButtonEvent mouse_event) {
        if (this->_mouse_input_config.contains(mouse_event.button)) {
            this->_input_model->release(this->_mouse_input_config[mouse_event.button]);
        }
    }

    /**
     * propagate scroll mouse wheel event to input model
     * @param mouse_wheel_event event to propagate
     */
    virtual void handle_scrolling(SDL_MouseWheelEvent mouse_wheel_event) {
        this->_input_model->set_mouse_wheel({mouse_wheel_event.x, mouse_wheel_event.y});
    }

    /**
     * propagate window event to input model
     * @param window_event event to propagate
     */
    virtual void handle_window_event(SDL_WindowEvent window_event) {
        SDL_WindowEventID event_id = static_cast<SDL_WindowEventID>(window_event.event);
        if (this->_window_event_config.contains(event_id)) {
            this->_input_model->trigger(this->_window_event_config[event_id]);
        }
    }

public:

    /**
     * Constructor
     * @param input_model the applications input model
     * @param keyboard_input_config the applications keyboard input config
     * @param window_event_config the applicatoins window input config
     * @param mouse_input_config the applications mouse input config
     */
    InputController(InputModel<T> *input_model, std::map<SDL_Scancode, T> keyboard_input_config,
                    std::map<SDL_WindowEventID, T> window_event_config,
                    std::map<Uint8, T> mouse_input_config)
        : _input_model(input_model), _keyboard_input_config(keyboard_input_config),
        _window_event_config(window_event_config), _mouse_input_config(mouse_input_config) {}

    /**
     * Generate input state
     */
    virtual void update() override {
        this->_input_model->update();
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->_input_model->set_mouse_position({x, y});
        for (SDL_Event event: events()) {
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
