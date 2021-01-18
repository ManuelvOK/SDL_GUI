#pragma once

#include "../application.h"
#include "plugin_base.h"

#include "../controllers/input_controller.h"
#include "../controllers/interface_controller.h"
#include "../models/interface_model.h"
#include "../models/input_model.h"
#include "../views/interface_view.h"

#include "../config/input_config.h"
#include "../input_keys.h"

namespace SDL_GUI {

/** Plugin that hold the default default GUI rendering */
class DefaultPlugin: public PluginBase {
private:
    ApplicationBase *_application;      /**< The application */
    InterfaceModel *_interface_model;   /**< The applications interface model */
    InputModel<InputKey> *_input_model; /**< The applications input model */
public:
    /** Constructor */
    DefaultPlugin() : PluginBase("DefaultPlugin") {}

    /**
     * Create all the needed Models, Controllers and Views
     * @tparam Ts List of already instantiated plugin types
     * @param app The application
     * @param previous tuple of already instantiated plugins
     * @param argc programs argc
     * @param argv[] programs argv
     */
    template <typename ... Ts>
    void init(ApplicationBase *app, std::tuple<Ts...> previous, int argc, char* argv[]) {
        (void)previous;
        (void)argc;
        (void)argv;
        this->_application = app;

        /* Models */
        this->_interface_model = new SDL_GUI::InterfaceModel(app->renderer(), app->window_width(),
                                                             app->window_height());
        app->add_model(this->_interface_model);

        this->_input_model = new InputModel<InputKey>();
        app->add_model(this->_input_model);

        /* Controllers */
        InputController<InputKey> *input_controller =
            new InputController<InputKey>(this->_input_model, keyboard_input_config,
                    window_event_config, mouse_input_config);
        app->add_controller(input_controller);

        InterfaceController *interface_controller = new InterfaceController("templates/main.tpl",
                                                                            this->_interface_model,
                                                                            this->_input_model);
        interface_controller->_weight = 200;
        app->add_controller(interface_controller);

        /* Views */
        InterfaceView *interface_view = new InterfaceView(app->renderer(), this->_interface_model);
        app->add_view(interface_view);
    }

    /**
     * Getter for _interface_model
     * @return this->_interface_model
     */
    InterfaceModel *interface_model();

    /**
     * Getter for _input_model
     * @return this->_input_model
     */
    InputModel<InputKey> *input_model();
};
}
