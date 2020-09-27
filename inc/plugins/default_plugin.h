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
class DefaultPlugin: public PluginBase {
private:
    ApplicationBase *_application;
    InterfaceModel *_interface_model;
    InputModel<InputKey> *_input_model;
public:
    DefaultPlugin() : PluginBase("DefaultPlugin") {
    }

    /**
     * creates all the needed Models, Controllers and Views
     */
    template <typename ... Ts>
    void init(ApplicationBase *app, std::tuple<Ts...> previous) {
        (void)previous;
        std::cout << "Default Plugin\n";
        this->_application = app;
        /**********
         * Models *
         **********/
        this->_interface_model = new SDL_GUI::InterfaceModel(app->renderer(), app->window_width(),
                                                             app->window_height());
        app->add_model(this->_interface_model);

        this->_input_model = new InputModel<InputKey>();
        app->add_model(this->_input_model);

        /***************
         * Controllers *
         ***************/
        InputController<InputKey> *input_controller =
            new InputController<InputKey>(this->_input_model, keyboard_input_config,
                    window_event_config, mouse_input_config);
        app->add_controller(input_controller);

        SDL_GUI::InterfaceController *interface_controller =
            new SDL_GUI::InterfaceController("templates/main.tpl", this->_interface_model,
                                             this->_input_model);
        app->add_controller(interface_controller);

        /*********
         * Views *
         *********/
        SDL_GUI::InterfaceView *interface_view =
            new SDL_GUI::InterfaceView(app->renderer(), this->_interface_model);
        app->add_view(interface_view);
    }

    InterfaceModel *interface_model() {
        return this->_interface_model;
    }

    InputModel<InputKey> *input_model() {
        return this->_input_model;
    }
};
}
