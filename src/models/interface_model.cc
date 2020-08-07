#include <models/interface_model.h>

#include <iostream>
#include <string>

using namespace SDL_GUI;

TTF_Font *InterfaceModel::_font;

InterfaceModel::InterfaceModel(SDL_Renderer *renderer, unsigned window_width, unsigned window_height) : _renderer(renderer), _window_width(window_width), _window_height(window_height) {
    this->init();
}

void InterfaceModel::init() {
    /* init font */
    this->_font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 12);
    if (!this->_font) {
        std::cerr << "TTF_Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}


TTF_Font *InterfaceModel::font() {
    return InterfaceModel::_font;
}

Drawable *InterfaceModel::drawable_root() {
    return this->_drawable_root;
}

const Drawable *InterfaceModel::drawable_root() const {
    return this->_drawable_root;
}

void InterfaceModel::set_drawable_root(Drawable *root) {
    this->_drawable_root = root;
}

SDL_Renderer *InterfaceModel::renderer() {
    return this->_renderer;
}

unsigned InterfaceModel::window_width() const {
    return this->_window_width;
}

unsigned InterfaceModel::window_height() const {
    return this->_window_height;
}

Drawable *InterfaceModel::null_drawable() const {
    return new NullDrawable();
}

std::vector<Drawable *> InterfaceModel::find_drawables(std::string attribute) {
    return this->_drawable_root->filter([attribute](Drawable *d){
        return d->has_attribute(attribute);
    });
}

std::vector<const Drawable *> InterfaceModel::find_drawables(std::string attribute) const {
    const Drawable *drawable_root = this->_drawable_root;
    return drawable_root->filter([attribute](const Drawable *d){
        return d->has_attribute(attribute);
    });
}

Drawable * InterfaceModel::find_first_drawable(std::string attribute) {
    std::vector<Drawable *> drawables = this->find_drawables(attribute);
    if (drawables.size() < 1) {
        return nullptr;
    }
    return drawables[0];
}

const Drawable * InterfaceModel::find_first_drawable(std::string attribute) const {
    std::vector<const Drawable *> drawables = this->find_drawables(attribute);
    if (drawables.size() < 1) {
        return nullptr;
    }
    return drawables[0];
}

Drawable *InterfaceModel::find_first_drawable_at_position(Position position) {
    return this->_drawable_root->find_first_bottom_up([position](Drawable *d){
        return d->is_inside(position);
    });
}

const Drawable *InterfaceModel::find_first_drawable_at_position(Position position) const {
    return this->_drawable_root->find_first_bottom_up([position](Drawable *d){
        return d->is_inside(position);
    });
}
