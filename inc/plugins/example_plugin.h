#pragma once

#include <map>

#include <SDL2/SDL.h>

#include "../application.h"

#include "../controllers/controller_base.h"
#include "plugin_base.h"
#include "default_plugin.h"

namespace SDL_GUI {

enum class ExampleInputKey {
    QUIT,
};

static const std::map<SDL_Scancode, ExampleInputKey> example_keyboard_input_config = {
    {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
    {SDL_SCANCODE_ESCAPE, ExampleInputKey::QUIT},
};

static const std::map<SDL_WindowEventID, ExampleInputKey> example_window_event_config;

static const std::map<Uint8, ExampleInputKey> example_mouse_input_config;

class ExampleController : public ControllerBase {
    ApplicationBase *_application;
    InputModel<ExampleInputKey> *_input_model;
public:
    ExampleController(ApplicationBase *application, InputModel<ExampleInputKey> *input_model)
        : _application(application), _input_model(input_model) {}

    virtual void update() {
        if (this->_input_model->is_pressed(ExampleInputKey::QUIT)) {
            this->_application->_is_running = false;
        }
    }
};

class ExamplePlugin: public PluginBase {
public:
    ExamplePlugin(): PluginBase("Example Plugin") {}

    template <typename ... Ts>
    void init(ApplicationBase *app, std::tuple<Ts...> previous, int argc, char *argv[]) {
        (void)app;
        (void)argc;
        (void)argv;
        /* Models */
        InputModel<ExampleInputKey> *input_model = new InputModel<ExampleInputKey>();
        app->add_model(input_model);

        /* Controllers */
        InputController<ExampleInputKey> *input_controller = new InputController<ExampleInputKey>(input_model, example_keyboard_input_config, example_window_event_config, example_mouse_input_config);
        app->add_controller(input_controller);

        ExampleController *example_controller = new ExampleController(app, input_model);
        app->add_controller(example_controller);

        DefaultPlugin &default_plugin = std::get<DefaultPlugin>(previous);
        InterfaceModel *interface_model = default_plugin.interface_model();
        Drawable *main = interface_model->find_first_drawable("main");
        Texture *t = new Texture("textures/strichmann.png", app->renderer());
        t->set_width(500);
        t->set_height(200);
        main->add_child(t);
    }
};
}
