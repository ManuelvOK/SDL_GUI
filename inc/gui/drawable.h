#pragma once

#include <functional>

#include <SDL2/SDL.h>

#include "attributable.h"
#include "position.h"
#include "positionable.h"
#include "scrollable.h"
#include "style.h"

namespace SDL_GUI {
class Drawable : public Positionable, public Scrollable, public Attributable {
protected:
    Style *_current_style = &this->_default_style;

    /**
     * default Contructor
     */
    Drawable() = default;

    /**
     * Constructor
     *
     * @param position
     *   local position inside parent drawable
     */
    Drawable(Position position) : Positionable(position) {}

    /**
     * vector of callbacks for recalculation
     */
    std::vector<std::function<void(Drawable *)>> _recalculation_callbacks;

    /**
     * function to call after current_style is set
     */
    virtual void hook_set_current_style(Style *style);
public:
    Style _default_style;
    Style _hover_style;

    /**
     * getter for _position
     *
     * @returns
     *   position
     */
    Position position() const;

    /**
     * draw this Object. gets called by render()
     *
     * @param renderer
     *   renderer to draw on
     * @param position
     *   global offset in window
     */
    virtual void draw(SDL_Renderer *renderer, Position position) const = 0;

    /**
     * change the style to use for rendering
     *
     * @param style
     *   style to use
     */
    void set_current_style(Style *style);

    /**
     * add a callback function for data binding
     * @param callback callback function that gets executed every tick
     */
    void add_recalculation_callback(std::function<void(Drawable *)> callback);

    /**
     * recalculate attributes of this drawable by calling all of the recalculation callbacks
     */
    void recalculate();

    /**
     * draw this and all of its childs
     *
     * @param renderer
     *   renderer to draw on
     * @param parent_position
     *   global offset of parent
     */
    //void render(SDL_Renderer *renderer, Position parent_position = {0,0}) const;

    /**
     * Find first Child that holds a given attribute
     *
     * @param attribute
     *   attribute to search for
     * @returns
     *   first found Drawable that holds the given attribute. nullptr if no such object exists.
     */
    //Drawable *find_first_with_attribute(std::string attribute);

    /**
     * Find all Childs that hold a given attribute
     *
     * @param attribute
     *   attribute to search for
     * @returns
     *   List of Objects that hold the given attribute.
     */
    //std::vector<Drawable *> find_all_with_attribute(std::string attribute);

    /**
     * check if Position is inside this
     *
     * @param position
     *   Position to check for
     * @returns
     *   True if position is inside. False otherwise.
     */
    virtual bool is_inside(Position position) const;

    /**
     * add a child
     *
     * @param child
     *   child to add
     */
    //void add_child(Drawable *child);

};
}
