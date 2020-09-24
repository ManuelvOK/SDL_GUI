#pragma once

#include "../application.h"

#include "../controllers/controller_base.h"
#include "plugin_base.h"
#include "default_plugin.h"

namespace SDL_GUI {

class ExampleController : public ControllerBase {
    ApplicationBase *_application;
    InputModel<InputKey> *_input_model;
public:
    ExampleController(ApplicationBase *application, InputModel<InputKey> *input_model)
        : _application(application), _input_model(input_model) {}

    virtual void update() {
        if (this->_input_model->is_pressed(InputKey::QUIT)) {
            this->_application->_is_running = false;
        }
    }
};

class ExamplePlugin: public PluginBase {
public:
    ExamplePlugin(): PluginBase("Example Plugin") {}

    template <typename ... Ts>
    void init(ApplicationBase *app, std::tuple<Ts...> previous) {
        (void)app;
        std::cout << "Example Plugin\n";
        DefaultPlugin &default_plugin = std::get<DefaultPlugin>(previous);
        InputModel<InputKey> *input_model = default_plugin.input_model();
        ExampleController *controller = new ExampleController(app, input_model);
        app->add_controller(controller);

        InterfaceModel *interface_model = default_plugin.interface_model();
        Drawable *main = interface_model->find_first_drawable("main");
        Texture *t = new Texture("textures/strichmann.png", app->renderer());
        t->set_width(500);
        t->set_height(200);
        main->add_child(t);
    }
};
}
