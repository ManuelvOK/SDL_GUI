#include <gui/drawable.h>

using namespace SDL_GUI;

Position Drawable::position() const {
    return this->_position;
}

void Drawable::set_current_style(Style *style) {
    this->_current_style = style;
    this->hook_set_current_style(style);
}

bool Drawable::has_hover_style() {
    return this->_has_hover_style;
}

void Drawable::hook_set_current_style(Style *style) {
    (void) style;
}

void Drawable::add_recalculation_callback(std::function<void(Drawable *)> callback) {
    this->_recalculation_callbacks.push_back(callback);
}

void Drawable::recalculate() {
    for (std::function<void(Drawable *)> callback: this->_recalculation_callbacks) {
        callback(this);
    }
}

void Drawable::show() {
    this->_current_style->_hidden = false;
}

void Drawable::hide() {
    this->_current_style->_hidden = true;
}

bool Drawable::is_hidden() const {
    return this->_current_style->_hidden;
}

bool Drawable::is_inside(Position position) const {
    return position._x > this->_position._x &&
           position._y > this->_position._y &&
           position._x < this->_position._x + static_cast<int>(this->_width) &&
           position._y < this->_position._y + static_cast<int>(this->_height);
}
