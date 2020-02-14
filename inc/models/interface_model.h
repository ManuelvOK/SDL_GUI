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
public:
    InterfaceModel();

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
};
}
