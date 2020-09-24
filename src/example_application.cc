#include <example_application.h>

#include <config/input_config.h>
#include <controllers/input_controller.h>
#include <controllers/interface_controller.h>
#include <models/interface_model.h>
#include <views/interface_view.h>

#include <gui/primitives/texture.h>

//using namespace SDL_GUI;
//
//void ExampleApplication::init_MVCs() {
//    /**********
//     * Models *
//     **********/
//    /* init input model */
//    InputModel<InputKey> *input_model = new InputModel<InputKey>();
//    this->_model_list.push_back(input_model);
//    this->_input_model = input_model;
//
//    /* init interface model */
//    InterfaceModel *interface_model = new InterfaceModel(this->_renderer, this->_window_width, this->_window_height);
//    this->_model_list.push_back(interface_model);
//
//    /***************
//     * Controllers *
//     ***************/
//
//    /* init input controller */
//    InputController<InputKey> *input_controller = new InputController<InputKey>(input_model, keyboard_input_config, window_event_config, mouse_input_config);
//    this->_controller_list.push_back(input_controller);
//
//    /* init interface controller */
//    InterfaceController *interface_controller = new InterfaceController("./templates/main.tpl", interface_model, input_model);
//    this->_controller_list.push_back(interface_controller);
//
//    /********
//     * View *
//     ********/
//    /* init interface view */
//    InterfaceView *interface_view = new InterfaceView(this->_renderer, interface_model);
//    this->_view_list.push_back(interface_view);
//
//
//    /*****************
//     * example stuff *
//     *****************/
//    Drawable *main = interface_model->find_first_drawable("main");
//    Texture *t = new Texture("textures/strichmann.png", this->_renderer);
//    t->set_width(500);
//    t->set_height(200);
//    main->add_child(t);
//}
//
//void ExampleApplication::update_running() {
//    if (this->_input_model->is_down(InputKey::QUIT)) {
//        this->_is_running = false;
//    }
//}
