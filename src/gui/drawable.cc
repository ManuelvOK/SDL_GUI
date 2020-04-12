#include <gui/drawable.h>

#include <sstream>

#include <gui/primitives/text.h>
#include <models/interface_model.h>

using namespace SDL_GUI;

Drawable::Drawable(std::string type, Position position, std::function<void ()> init_debug_information_callback) : Positionable(position), _type(type) {
    if (init_debug_information_callback) {
        this->_init_debug_information_callback = init_debug_information_callback;
    } else {
        this->_init_debug_information_callback = std::bind(&Drawable::default_init_debug_information, this);
    }
}

void Drawable::default_init_debug_information() {
    /* Position Text */
    std::stringstream position_string;
    position_string << this->position();

    Text *position_text = new Text(InterfaceModel::font(), position_string.str());
    position_text->set_position({3,3});
    position_text->add_attribute("debug");
    Drawable *drawable = this;
    position_text->add_recalculation_callback([drawable, position_text](Drawable *){
            std::stringstream position_string;
            position_string << drawable->position();
            position_text->set_text(position_string.str());
        });

    this->_debug_information.push_back(position_text);
}

void Drawable::init_debug_information() {
    if (this->_debug_information_initialised) {
        return;
    }
    this->_init_debug_information_callback();
    this->_debug_information_initialised = true;
}

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

void Drawable::draw_border(SDL_Renderer *renderer, Position position) const {
    if (not this->_current_style->_has_border) {
        return;
    }
    for (int i = 0; i < static_cast<int>(this->_current_style->_border_width); ++i) {
        SDL_Rect r = {
            position._x + i,
            position._y + i,
            static_cast<int>(this->_width - 2*i),
            static_cast<int>(this->_height - 2*i),
        };
        this->_current_style->_border_color.activate(renderer);
        SDL_RenderDrawRect(renderer, &r);
        /* since the drawn rect does not include the lower right point,
         * we have to draw it manually */
        SDL_RenderDrawPoint(renderer, r.x + r.w - 1, r.y + r.h - 1);
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
