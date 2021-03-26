#pragma once

#include <map>

#include <SDL2/SDL.h>

#include "../application.h"

#include "../controllers/controller_base.h"
#include "plugin_base.h"
#include "default_plugin.h"

namespace SDL_GUI {

/**
 * Abstraction for all possible inputs this plugin handles
 * For this Example its only important to close the application
 */
enum class ExampleInputKey {
    QUIT,
    DEBUG,
};

/**
 * Keyboard input config.
 * Keypresses of `[ESC]` and `[Q]` both will result in quitting the application
 */
static const std::map<std::set<SDL_Scancode>, std::map<SDL_Scancode, ExampleInputKey>>
example_keyboard_input_config = {
    {{}, {
        {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
        {SDL_SCANCODE_ESCAPE, ExampleInputKey::QUIT},
    }},
    {{SDL_SCANCODE_LSHIFT}, {
        {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
        {SDL_SCANCODE_D, ExampleInputKey::DEBUG},
    }},
    {{SDL_SCANCODE_RSHIFT}, {
        {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
        {SDL_SCANCODE_D, ExampleInputKey::DEBUG},
    }},
};

/**
 * Window event config.
 * This could be used to react to changes in the window size.
 */
static const std::map<SDL_WindowEventID, ExampleInputKey> example_window_event_config;

/**
 * Mouse input config
 * This could be used to react to mouse clicks or movements or scrolling.
 */
static const std::map<std::set<SDL_Scancode>, std::map<Uint8, ExampleInputKey>> example_mouse_input_config;

/** Plugins controller */
class ExampleController : public ControllerBase {
    ApplicationBase *_application;              /**< The application */
    InputModel<ExampleInputKey> *_input_model;  /**< The applications input model */
    InterfaceModel *_interface_model;
public:
    /**
     * Constructor
     * @param application The application
     * @param input_model The applications input model
     */
    ExampleController(ApplicationBase *application, InputModel<ExampleInputKey> *input_model,
                      InterfaceModel *interface_model)
        : _application(application), _input_model(input_model), _interface_model(interface_model) {}

    /**
     * Check if application should quit
     */
    virtual void update() {
        if (this->_input_model->is_pressed(ExampleInputKey::QUIT)) {
            this->_application->_is_running = false;
        }
        if (this->_input_model->is_down(ExampleInputKey::DEBUG)) {
            this->_interface_model->toggle_debug_information_drawn();
        }
    }
};

/** The Plugin we use to show what this library can do */
class ExamplePlugin: public PluginBase {
    InterfaceModel *_interface_model;
public:
    /** Constructor */
    ExamplePlugin(): PluginBase("Example Plugin") {}

    /**
     * Create all the needed Models, Controllers and Views
     * @tparam Ts List of already instantiated plugin types
     * @param app The application
     * @param previous tuple of already instantiated plugins
     * @param argc programs argc
     * @param argv[] programs argv
     */
    template <typename ... Ts>
    void init(ApplicationBase *app, std::tuple<Ts...> previous, int argc, char *argv[]) {
        (void)app;
        (void)argc;
        (void)argv;
        /* Models */
        InputModel<ExampleInputKey> *input_model = new InputModel<ExampleInputKey>();
        app->add_model(input_model);

        /* Controllers */
        InputController<ExampleInputKey> *input_controller =
            new InputController<ExampleInputKey>(input_model, example_keyboard_input_config,
                                                 example_window_event_config,
                                                 example_mouse_input_config);
        app->add_controller(input_controller);

        DefaultPlugin &default_plugin = std::get<DefaultPlugin>(previous);
        this->_interface_model = default_plugin.interface_model();

        ExampleController *example_controller = new ExampleController(app, input_model,
                                                                      this->_interface_model);
        app->add_controller(example_controller);

        Drawable *main = this->_interface_model->find_first_drawable("main");
        Texture *t = new Texture("textures/strichmann.png", app->renderer());
        t->set_width(500);
        t->set_height(200);
        main->add_child(t);
    }
};
}
