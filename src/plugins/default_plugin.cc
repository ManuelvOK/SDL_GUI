#include <plugins/default_plugin.h>

using namespace SDL_GUI;

InterfaceModel *DefaultPlugin::interface_model() {
    return this->_interface_model;
}

InputModel<InputKey> *DefaultPlugin::input_model() {
    return this->_input_model;
}
