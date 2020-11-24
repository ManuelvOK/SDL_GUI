#pragma once

#include <SDL2/SDL_ttf.h>

#include "model_base.h"
#include "../gui/drawable.h"

namespace SDL_GUI {
/** Model for all the Data related to the grafical interface that actually gets rendered */
class InterfaceModel : public ModelBase {
protected:
    static TTF_Font *_font;     /**< Font to use for text */
    Drawable *_drawable_root;   /**< Tree of Drawables that get rendered */
    SDL_Renderer *_renderer;    /**< The applications renderer */
    unsigned _window_width;     /**< applications windows width */
    unsigned _window_height;    /**< applications windows height */
    Drawable *_null_drawable;   /**< drawable tombstone */
public:
    /**
     * Constructor
     * @param renderer The applications renderer
     * @param window_width The applications windows width
     * @param window_height The applications windows height
     */
    InterfaceModel(SDL_Renderer *renderer, unsigned window_width, unsigned window_height);

    /** Destructor */
    ~InterfaceModel();

    /**
     * Getter for _font
     * @return this->_font
     */
    static TTF_Font *font();

    /**
     * Getter for _drawable_root
     * @return this->_drawable_root
     */
    Drawable *drawable_root();

    /** @copydoc drawable_root() */
    const Drawable *drawable_root() const;

    /**
     * Setter for _drawable_root
     * @param root drawable root
     */
    void set_drawable_root(Drawable *root);

    /**
     * Getter for _renderer
     * @return this->_renderer
     */
    SDL_Renderer *renderer();

    /**
     * Getter for _window_width
     * @return this->_window_width
     */
    unsigned window_width() const;

    /**
     * Getter for _window_height
     * @return this->_window_height
     */
    unsigned window_height() const;

    /**
     * Getter for _null_drawable
     * @return this->_null_drawable
     */
    Drawable *null_drawable() const;

    /**
     * find all Drawables in _drawable_root with a certain attribute
     * @param attribute attribute to find
     * @return vector of found drawables
     */
    std::vector<Drawable *> find_drawables(std::string attribute);

    /** @copydoc find_drawables(std::string) */
    std::vector<const Drawable *> find_drawables(std::string attribute) const;

    /**
     * find first Drawable in _drawable_root with a certain attribute
     * @param attribute attribute to find
     * @return first drawable with the given attribute
     */
    Drawable *find_first_drawable(std::string attribute);

    /** @copydoc find_first_drawable(std::string) */
    const Drawable *find_first_drawable(std::string attribute) const;

    /**
     * get bottommost drawable in tree whose bounding box surrounds a given position
     * This gets the first drawable the mouse hovers over
     * @param position position to look at
     * @return first drawable at given position
     */
    Drawable *find_first_drawable_at_position(Position position);

    /** @copydoc find_first_drawable_at_position(Position) */
    const Drawable *find_first_drawable_at_position(Position position) const;
};
}
