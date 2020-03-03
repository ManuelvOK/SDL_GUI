#include <models/input_model.h>

using namespace SDL_GUI;

void InputModelBase::set_position(Position position) {
    this->_current_position = position;
}

Position InputModelBase::current_position() const {
    return this->_current_position;
}
