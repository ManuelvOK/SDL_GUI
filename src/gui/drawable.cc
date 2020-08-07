#include <gui/drawable.h>

#include <sstream>

#include <gui/primitives/text.h>
#include <models/interface_model.h>

using namespace SDL_GUI;

Drawable::Drawable(std::string type, Position parent_position, Position position, std::function<void ()> init_debug_information_callback) : Positionable(position, parent_position), _type(type) {
    if (init_debug_information_callback) {
        this->_init_debug_information_callback = init_debug_information_callback;
    } else {
        this->_init_debug_information_callback = std::bind(&Drawable::default_init_debug_information, this);
    }
}

Drawable *Drawable::parent() {
    return this->_parent;
}

std::list<Drawable *> Drawable::children(bool reversed) {
    return reversed ? this->_children_reversed : this->_children;
}

const std::list<Drawable *> Drawable::children(bool reversed) const {
    return reversed ? this->_children_reversed : this->_children;
}

void Drawable::add_child(Drawable *child) {
    this->_children.push_back(child);
    this->_children_reversed.push_front(child);
    child->init_debug_information();
}

void Drawable::add_children(std::vector<Drawable *> children) {
    for (Drawable *child: children) {
        this->add_child(child);
    }
}

Drawable *Drawable::find_first(std::function<bool (Drawable *)> f) {
    if (f(this)) {
        return this;
    }
    Drawable *found = nullptr;
    for (Drawable *d: this->_children) {
        found = d->find_first(f);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

Drawable *Drawable::find_first_bottom_up(std::function<bool (Drawable *)> f) {
    Drawable *found = nullptr;
    for (Drawable *d: this->_children) {
        found = d->find_first_bottom_up(f);
        if (found != nullptr) {
            return found;
        }
    }
    if (f(this)) {
        return this;
    }
    return nullptr;
}

std::vector<Drawable *> Drawable::filter(std::function<bool (Drawable *)> f) {
    std::vector<Drawable *> filtered;
    if (f(this)) {
        filtered.push_back(this);
    }
    for (Drawable *d: this->_children) {
        std::vector<Drawable *> filtered_child = d->filter(f);
        filtered.insert(filtered.end(), filtered_child.begin(), filtered_child.end());
    }
    return filtered;
}

std::vector<const Drawable *> Drawable::filter(std::function<bool (const Drawable *)> f) const {
    std::vector<const Drawable *> filtered;
    if (f(this)) {
        filtered.push_back(this);
    }
    for (const Drawable *d: this->_children) {
        std::vector<const Drawable *> filtered_child = d->filter(f);
        filtered.insert(filtered.end(), filtered_child.begin(), filtered_child.end());
    }
    return filtered;
}

void Drawable::map(std::function<void (Drawable *)> f, bool reversed) {
    f(this);
    for (Drawable *d: this->children(reversed)) {
        d->map(f, reversed);
    }
}

void Drawable::bottom_up_map(std::function<void (Drawable *)> f, bool reversed) {
    for (Drawable *d: this->children(reversed)) {
        d->map(f, reversed);
    }
    f(this);
}

void Drawable::default_init_debug_information() {
    /* Position Text */
    std::stringstream position_string;
    position_string << this->position();
    std::stringstream attribute_string;
    for (std::string attribute: this->_attributes) {
        attribute_string << attribute;
    }
    if (attribute_string.str().empty()) {
        attribute_string << "--noname--";
    }

    Text *position_text = new Text(InterfaceModel::font(), position_string.str());
    position_text->set_position({3,3});
    position_text->add_attribute("debug");
    Drawable *drawable = this;
    position_text->add_recalculation_callback([drawable, position_text](Drawable *){
            std::stringstream position_string;
            position_string << drawable->absolute_position();
            position_text->set_text(position_string.str());
        });
    this->_debug_information.push_back(position_text);

    Text *attribute_text = new Text(InterfaceModel::font(), attribute_string.str());
    attribute_text->set_position({3,16});
    attribute_text->add_attribute("debug");
    this->_debug_information.push_back(attribute_text);
}

void Drawable::init_debug_information() {
    if (this->_debug_information_initialised) {
        return;
    }
    this->_init_debug_information_callback();
    this->_debug_information_initialised = true;
}

void Drawable::move(Position position) {
    Positionable::move(position);
    for (Drawable *child: this->_children) {
        child->map([position](Drawable *d){
            d->move_absolute(position);
        });
    }
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
