#include <models/mouse_input_model.h>

using namespace SDL_GUI;

void MouseInputModel::update() {
    for (bool &state: this->_current_states) {
        state = false;
    }
}
void MouseInputModel::set_pressed(Button button) {
    this->_current_states[static_cast<unsigned>(button)] = true;
}

void MouseInputModel::set_position(Position position) {
    this->_current_position = position;
}

bool MouseInputModel::is_pressed(Button button) const {
    return this->_current_states[static_cast<unsigned>(button)];
}

Position MouseInputModel::current_position() const {
    return this->_current_position;
}
