#pragma once

#include <SDL2/SDL_ttf.h>

#include "model_base.h"
#include "../gui/drawable.h"

namespace SDL_GUI {
class InterfaceModel : public ModelBase {
protected:
    /**
     * Font to us for text
     */
    static TTF_Font *_font;

    /**
     * Tree of Drawables that get rendered
     */
    Drawable *_drawable_root;

    SDL_Renderer *_renderer;

    unsigned _window_width;
    unsigned _window_height;
public:
    InterfaceModel(SDL_Renderer *renderer, unsigned window_width, unsigned window_height);
    ~InterfaceModel() = default;

    virtual void init();

    /**
     * getter for _font
     * @returns this->_font
     */
    static TTF_Font *font();

    /**
     * getter for _drawable_root
     * @returns this->_drawable_root
     */
    Drawable *drawable_root();
    const Drawable *drawable_root() const;

    /**
     * setter for _drawableroote
     */
    void set_drawable_root(Drawable *root);

    SDL_Renderer *renderer();

    unsigned window_width() const;
    unsigned window_height() const;

    Drawable *null_drawable() const;

    /**
     * find all Drawables in _drawable_root with a certain attribute
     * @param attribute attribute to find
     */
    std::vector<Drawable *> find_drawables(std::string attribute);
    std::vector<const Drawable *> find_drawables(std::string attribute) const;

    /**
     * find first Drawable in _drawable_root with a certain attribute
     * @param attribute attribute to find
     */
    Drawable *find_first_drawable(std::string attribute);
    const Drawable *find_first_drawable(std::string attribute) const;

    /**
     * get bottommost drawable in tree whose bounding box surrounds a given position
     * This gets the first drawable the mouse hovers over
     */
    Drawable *find_first_drawable_at_position(Position position);
    const Drawable *find_first_drawable_at_position(Position position) const;
};
}
