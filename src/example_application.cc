#include <example_application.h>

#include <config/input_config.h>
#include <controllers/input_controller.h>
#include <controllers/interface_controller.h>
#include <models/interface_model.h>
#include <views/interface_view.h>

using namespace SDL_GUI;

void ExampleApplication::init_MVCs() {
    /**********
     * Models *
     **********/
    /* init input model */
    InputModel<InputKey> *input_model = new InputModel<InputKey>();
    this->_model_list.push_back(input_model);
    this->_input_model = input_model;

    /* init interface model */
    InterfaceModel *interface_model = new InterfaceModel();
    this->_model_list.push_back(interface_model);

    /***************
     * Controllers *
     ***************/

    /* init input controller */
    InputController<InputKey> *input_controller = new InputController<InputKey>(input_model, input_config);
    this->_controller_list.push_back(input_controller);

    /* init interface controller */
    InterfaceController *interface_controller = new InterfaceController("./templates/main.tpl", interface_model, input_model);
    this->_controller_list.push_back(interface_controller);

    /********
     * View *
     ********/
    /* init interface view */
    InterfaceView *interface_view = new InterfaceView(this->_renderer, interface_model);
    this->_view_list.push_back(interface_view);
}

void ExampleApplication::update_running() {
    if (this->_input_model->is_down(InputKey::QUIT)) {
        this->_is_running = false;
    }
}
