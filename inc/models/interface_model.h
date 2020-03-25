#pragma once

#include <SDL2/SDL_ttf.h>

#include "model_base.h"
#include "../gui/drawable.h"
#include "../util/tree.h"

namespace SDL_GUI {
class InterfaceModel : public ModelBase {
protected:
    /**
     * Font to us for text
     */
    TTF_Font *_font;

    /**
     * Tree of Drawables that get rendered
     */
    Tree<Drawable> *_drawable_tree;

    NullDrawable *_null_drawable;
    TreeNode<Drawable> *_null_drawable_node;
    SDL_Renderer *_renderer;
public:
    InterfaceModel(SDL_Renderer *renderer);
    ~InterfaceModel();

    virtual void init();

    /**
     * getter for _font
     * @returns this->_font
     */
    TTF_Font *font() const;

    /**
     * getter for _drawable_tree
     * @returns this->_drawable_tree
     */
    Tree<Drawable> *drawable_tree();
    const Tree<Drawable> *drawable_tree() const;

    /**
     * setter for _drawable_tree
     */
    void set_drawable_tree(Tree<Drawable> *tree);

    /**
     * find all Drawables in _drawable_tree with a certain attribute
     * @param attribute attribute to find
     */
    std::vector<Drawable *> find_drawables(std::string attribute);
    std::vector<const Drawable *> find_drawables(std::string attribute) const;

    /**
     * find first Drawable in _drawable_tree with a certain attribute
     * @param attribute attribute to find
     */
    Drawable * find_first_drawable(std::string attribute);
    const Drawable * find_first_drawable(std::string attribute) const;

    /**
     * find all TreeNodes in _drawable_tree with a certain attribute
     * @param attribute attribute to find
     */
    std::vector<TreeNode<Drawable> *> find_tree_nodes(std::string attribute);
    std::vector<const TreeNode<Drawable> *> find_tree_nodes(std::string attribute) const;

    /**
     * find first TreeNode in _drawable_tree with a certain attribute
     * @param attribute attribute to find
     */
    TreeNode<Drawable> * find_first_tree_node(std::string attribute);
    const TreeNode<Drawable> * find_first_tree_node(std::string attribute) const;
};
}
