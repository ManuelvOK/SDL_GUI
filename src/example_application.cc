#include <example_application.h>

#include <config/input_config.h>
#include <controllers/keyboard_input_controller.h>
#include <controllers/mouse_input_controller.h>
#include <controllers/interface_controller.h>
#include <models/interface_model.h>
#include <views/interface_view.h>

using namespace SDL_GUI;

void ExampleApplication::init_MVCs() {
    /**********
     * Models *
     **********/
    /* init keyboard input model */
    KeyboardInputModel<InputKey> *keyboard_input_model = new KeyboardInputModel<InputKey>();
    this->_model_list.push_back(keyboard_input_model);
    this->_keyboard_input_model = keyboard_input_model;

    /* init keyboard input model */
    MouseInputModel *mouse_input_model = new MouseInputModel();
    this->_model_list.push_back(mouse_input_model);

    /* init interface model */
    InterfaceModel *interface_model = new InterfaceModel();
    this->_model_list.push_back(interface_model);

    /***************
     * Controllers *
     ***************/

    /* init keyboard input controller */
    KeyboardInputController<InputKey> *keyboard_input_controller = new KeyboardInputController<InputKey>(keyboard_input_model, input_config);
    this->_controller_list.push_back(keyboard_input_controller);

    /* init mouse input controller */
    MouseInputController *mouse_input_controller = new MouseInputController();
    mouse_input_controller->set_model(mouse_input_model);
    this->_controller_list.push_back(mouse_input_controller);

    /* init interface controller */
    InterfaceController *interface_controller = new InterfaceController("./templates/main.tpl", interface_model, mouse_input_model);
    this->_controller_list.push_back(interface_controller);

    /********
     * View *
     ********/
    /* init interface view */
    InterfaceView *interface_view = new InterfaceView(this->_renderer, interface_model);
    this->_view_list.push_back(interface_view);
}

void ExampleApplication::update_running() {
    if (this->_keyboard_input_model->is_down(InputKey::QUIT)) {
        this->_is_running = false;
    }
}
