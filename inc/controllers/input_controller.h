#pragma once

#include <SDL2/SDL.h>

#include <algorithm>
#include <map>
#include <set>
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

/** Clear event vector. */
void clear_sdl_events();


/**
 * Getter for the events vector.
 * @return the events vector
 */
const std::vector<SDL_Event> events();

class LowLevelInputModel: public InputModel<SDL_Scancode> {
    std::set<Uint8> _button_pressed;
    std::set<Uint8> _button_down;
    std::set<Uint8> _button_up;

public:
    const std::set<Uint8> button_pressed() const;
    const std::set<Uint8> button_down() const;
    const std::set<Uint8> button_up() const;

    void press(Uint8 button);
    void trigger(Uint8 button);
    void release(Uint8 button);

    void update() override;
};

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

    LowLevelInputModel *_low_level_input_model = nullptr;

    /** the applications keyboard input config */
    std::map<std::set<SDL_Scancode>, std::map<SDL_Scancode, T>> _keyboard_input_config;

    /** the applications window event config */
    std::map<SDL_WindowEventID, T> _window_event_config;

    /** the applications mouse input config */
    std::map<std::set<SDL_Scancode>, std::map<Uint8, T>> _mouse_input_config;

    std::set<SDL_Scancode> _modifiers;


    /**
     * propagate key press to low level input model
     * @param kb_event event to propagate
     */
    virtual void handle_key_press(SDL_KeyboardEvent kb_event) {
        if (kb_event.repeat) {
                return;
            }
        this->_low_level_input_model->InputModel<SDL_Scancode>::press(kb_event.keysym.scancode);
    }

    /**
     * propagate key release to low level input model
     * @param kb_event event to propagate
     */
    virtual void handle_key_release(SDL_KeyboardEvent kb_event) {
        this->_low_level_input_model->InputModel<SDL_Scancode>::release(kb_event.keysym.scancode);
    }

    /**
     * propagate mouse button press to low level input model
     * @param mouse_event event to propagate
     */
    virtual void handle_button_press(SDL_MouseButtonEvent mouse_event) {
        this->_low_level_input_model->press(mouse_event.button);
    }

    /**
     * propagate mouse button release to low level input model
     * @param mouse_event event to propagate
     */
    virtual void handle_button_release(SDL_MouseButtonEvent mouse_event) {
        this->_low_level_input_model->release(mouse_event.button);
    }

    /**
     * propagate scroll mouse wheel event to low level input model
     * @param mouse_wheel_event event to propagate
     */
    virtual void handle_scrolling(SDL_MouseWheelEvent mouse_wheel_event) {
        this->_low_level_input_model->set_mouse_wheel({mouse_wheel_event.x, mouse_wheel_event.y});
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

    void register_high_level_input() {
        /* get set of pressed modifiers and load relevant config for that set */
        const std::set<SDL_Scancode> ll_pressed = this->_low_level_input_model->pressed();
        std::set<SDL_Scancode> pressed_modifiers;
        std::set_intersection(this->_modifiers.begin(), this->_modifiers.end(), ll_pressed.begin(), ll_pressed.end(), std::inserter(pressed_modifiers, pressed_modifiers.begin()));
        std::map<SDL_Scancode, T> relevant_keyboard_config =
            this->_keyboard_input_config[pressed_modifiers];
        std::map<Uint8, T> relevant_mouse_config =
            this->_mouse_input_config[pressed_modifiers];

        /* look up key presses */
        for (SDL_Scancode input: this->_low_level_input_model->down()) {
            if (relevant_keyboard_config.contains(input)) {
                this->_input_model->press(relevant_keyboard_config[input]);
            }
        }

        /* look up key releases */
        for (SDL_Scancode input: this->_low_level_input_model->up()) {
            if (relevant_keyboard_config.contains(input)) {
                this->_input_model->release(relevant_keyboard_config[input]);
            }
        }

        /* look up button presses */
        for (Uint8 input: this->_low_level_input_model->button_down()) {
            if (relevant_mouse_config.contains(input)) {
                this->_input_model->press(relevant_mouse_config[input]);
            }
        }

        /* look up button release */
        for (Uint8 input: this->_low_level_input_model->button_up()) {
            if (relevant_mouse_config.contains(input)) {
                this->_input_model->release(relevant_mouse_config[input]);
            }
        }

        /* handle modifier releases */
        auto ll_up = this->_low_level_input_model->up();
        std::set<SDL_Scancode> released_modifiers;
        std::set_intersection(this->_modifiers.begin(), this->_modifiers.end(), ll_up.begin(), ll_up.end(), std::inserter(released_modifiers, released_modifiers.begin()));

        /* check wich configs have this modifier */
        std::set<std::map<SDL_Scancode, T>> released_configs;
        for (const auto &[modifiers, config]: this->_keyboard_input_config) {
            std::set<SDL_Scancode> intersect;
            std::set_intersection(released_modifiers.begin(), released_modifiers.end(), modifiers.begin(), modifiers.end(), std::inserter(intersect, intersect.begin()));
            if (not intersect.empty()) {
                released_configs.insert(config);
            }
        }

        /* release everything that could be down */
        for (const auto &config: released_configs) {
            for (const auto &[_, input]: config) {
                this->_input_model->release(input);
            }
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
    InputController(InputModel<T> *input_model,
                    std::map<std::set<SDL_Scancode>, std::map<SDL_Scancode, T>> keyboard_input_config,
                    std::map<SDL_WindowEventID, T> window_event_config,
                    std::map<std::set<SDL_Scancode>, std::map<Uint8, T>> mouse_input_config)
        : _input_model(input_model), _keyboard_input_config(keyboard_input_config),
        _window_event_config(window_event_config), _mouse_input_config(mouse_input_config) {
        this->_low_level_input_model = new LowLevelInputModel();
        for (const auto &[modifier, _]: this->_keyboard_input_config) {
            this->_modifiers.insert(modifier.begin(), modifier.end());
        }
        for (const auto &[modifier, _]: this->_mouse_input_config) {
            this->_modifiers.insert(modifier.begin(), modifier.end());
        }
    }

    ~InputController() {
        delete this->_low_level_input_model;
    }


    /** Generate input state */
    virtual void update() override {
        this->_low_level_input_model->update();
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->_input_model->set_mouse_position({x, y});
        /* register keys and buttons */
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
        /* calculate high level inputs */
        this->_input_model->update();
        this->register_high_level_input();
    }
};
}
