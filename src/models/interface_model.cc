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

Tree<Drawable> *InterfaceModel::drawable_tree() {
    return this->_drawable_tree;
}

const Tree<Drawable> *InterfaceModel::drawable_tree() const {
    return this->_drawable_tree;
}

void InterfaceModel::set_drawable_tree(Tree<Drawable> *tree) {
    this->_drawable_tree = tree;
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

TreeNode<Drawable> *InterfaceModel::null_drawable_node() const {
    return new TreeNode<Drawable>(this->null_drawable());
}

std::vector<Drawable *> InterfaceModel::find_drawables(std::string attribute) {
    std::vector<TreeNode<Drawable> *> treenodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    std::vector<Drawable *> drawables;
    for (TreeNode<Drawable> *node: treenodes) {
        drawables.push_back(node->node());
    }
    return drawables;
}

std::vector<const Drawable *> InterfaceModel::find_drawables(std::string attribute) const {
    std::vector<TreeNode<Drawable> *> treenodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    std::vector<const Drawable *> drawables;
    for (TreeNode<Drawable> *node: treenodes) {
        drawables.push_back(node->node());
    }
    return drawables;
}

Drawable * InterfaceModel::find_first_drawable(std::string attribute) {
    std::vector<TreeNode<Drawable> *> treenodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    if (treenodes.size() < 1) {
        return nullptr;
    }
    return treenodes[0]->node();
}

const Drawable * InterfaceModel::find_first_drawable(std::string attribute) const {
    std::vector<TreeNode<Drawable> *> treenodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    if (treenodes.size() < 1) {
        return nullptr;
    }
    return treenodes[0]->node();
}

std::vector<TreeNode<Drawable> *> InterfaceModel::find_tree_nodes(std::string attribute) {
    return this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
}

std::vector<const TreeNode<Drawable> *> InterfaceModel::find_tree_nodes(std::string attribute) const {
    std::vector<TreeNode<Drawable> *> tree_nodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    return std::vector<const TreeNode<Drawable> *>(tree_nodes.begin(), tree_nodes.end());
}

TreeNode<Drawable> * InterfaceModel::find_first_tree_node(std::string attribute) {
    std::vector<TreeNode<Drawable> *> tree_nodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    if (tree_nodes.size() < 1) {
        return this->null_drawable_node();
    }
    return tree_nodes[0];
}

const TreeNode<Drawable> * InterfaceModel::find_first_tree_node(std::string attribute) const {
    std::vector<TreeNode<Drawable> *> tree_nodes = this->_drawable_tree->filter([attribute](Drawable *d){return d->has_attribute(attribute);});
    if (tree_nodes.size() < 1) {
        return this->null_drawable_node();
    }
    return tree_nodes[0];
}

Drawable *InterfaceModel::find_first_drawable_at_position(Position position) {
    TreeNode<Drawable> *node = this->_drawable_tree->find_first_bottom_up([position](Drawable *drawable){
            return drawable->is_inside(position);
        });
    if (node == nullptr) {
        return nullptr;
    }
    return node->node();
}

const Drawable *InterfaceModel::find_first_drawable_at_position(Position position) const {
    TreeNode<Drawable> *node = this->_drawable_tree->find_first_bottom_up([position](Drawable *drawable){
            return drawable->is_inside(position);
        });
    if (node == nullptr) {
        return nullptr;
    }
    return node->node();
}
