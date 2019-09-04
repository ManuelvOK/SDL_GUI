#include <model/input_model.h>

void InputModel::update() {
    for (bool &state: this->_current_states) {
        state = false;
    }
}
void InputModel::set_pressed(InputKey key) {
    this->_current_states[static_cast<unsigned>(key)] = true;
}

bool InputModel::is_pressed(InputKey key) const {
    return this->_current_states[static_cast<unsigned>(key)];
}
