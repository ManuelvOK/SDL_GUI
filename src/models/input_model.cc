#include <models/input_model.h>

using namespace SDL_GUI;

void InputModelBase::set_mouse_position(Position position) {
    this->_mouse_offset = position - this->_mouse_position;
    this->_mouse_position = position;
}

Position InputModelBase::mouse_position() const {
    return this->_mouse_position;
}

Position InputModelBase::mouse_offset() const {
    return this->_mouse_offset;
}

void InputModelBase::set_mouse_wheel(Position offset) {
    this->_mouse_wheel = offset;
}

Position InputModelBase::mouse_wheel() const {
    return this->_mouse_wheel;
}
