#include <models/interface_model.h>

#include <iostream>

using namespace SDL_GUI;

InterfaceModel::InterfaceModel() {
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

TTF_Font *InterfaceModel::font() const {
    return this->_font;
}

Tree<Drawable> *InterfaceModel::drawable_tree() {
    return this->_drawable_tree;
}

const Tree<Drawable> *InterfaceModel::drawable_tree() const {
    return this->_drawable_tree;
}

void InterfaceModel::set_drawable_tree(Tree<Drawable> *tree) {
    this->_drawable_tree = tree;
}
