#include <gui/drawable.h>

void Drawable::set_current_style(Style *style) {
    this->_current_style = style;
    this->hook_set_current_style(style);
}

void Drawable::hook_set_current_style(Style *style) {}

std::list<Drawable *> Drawable::children(bool reversed) {
    return reversed ? this->_children_reversed : this->_children;
}

void Drawable::map(std::function<void (Drawable *)> f, bool reversed) {
    f(this);
    for (Drawable *child: this->children(reversed)) {
        child->map(f);
    }
}

void Drawable::bottom_up_map(std::function<void (Drawable *)> f, bool reversed) {
    for (Drawable *child: this->children(reversed)) {
        child->map(f);
    }
    f(this);
}

template<typename T>
void Drawable::reduce(std::function<T (Drawable *, T)> f, T value, bool reversed) {
    T this_value = f(this, value);
    for (Drawable *child: this->children(reversed)) {
        child->reduce(f, this_value);
    }
}

template<typename T>
T Drawable::bottom_up_reduce(std::function<T (Drawable *, T)> f, T value,
        std::function<T (std::vector<T>)> aggregate, bool reversed) {
    if (this->_children.empty()) {
        return f(this, value);
    }
    std::vector<T> vec;
    for (Drawable *child: this->children(reversed)) {
        vec.push_back(child->reduce(f, value, aggregate));
    }
    return f(this, aggregate(vec));
}


void Drawable::render(SDL_Renderer *renderer, Position parent_position) const {
    Position position = parent_position + this->_position;
    this->draw(renderer, position);
    for (Drawable *child: this->_children) {
        if (child == nullptr) {
            continue;
        }
        child->render(renderer, position);
    }
}

Drawable *Drawable::find_first_with_attribute(std::string attribute) {
    if (this->has_attribute(attribute)) {
        return this;
    }
    for(Drawable *child: this->_children) {
        Drawable *found = child->find_first_with_attribute(attribute);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::vector<Drawable *> Drawable::find_all_with_attribute(std::string attribute) {
    std::vector<Drawable *> vec;
    if (this->has_attribute(attribute)) {
        vec.push_back(this);
    }
    for(Drawable *child: this->_children) {
        std::vector<Drawable *> found = child->find_all_with_attribute(attribute);
        vec.insert(vec.end(), found.begin(), found.end());
    }
    return vec;
}

bool Drawable::is_inside(Position position) const {
    return position._x > this->_position._x &&
           position._y > this->_position._y &&
           position._x < this->_position._x + static_cast<int>(this->_width) &&
           position._y < this->_position._y + static_cast<int>(this->_height);
}

void Drawable::add_child(Drawable *child) {
    this->_children.push_back(child);
    this->_children_reversed.push_front(child);
}
