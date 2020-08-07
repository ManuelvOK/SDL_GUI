#pragma once

#include <functional>
#include <list>

#include <SDL2/SDL.h>

#include "attributable.h"
#include "debuggable.h"
#include "hoverable.h"
#include "position.h"
#include "positionable.h"
#include "scrollable.h"
#include "style.h"

namespace SDL_GUI {
class Drawable : public Positionable, public Hoverable, public Scrollable, public Attributable, public Debuggable {
    Drawable *_parent;
    std::list<Drawable *> _children;
    std::list<Drawable *> _children_reversed;
protected:
    Style *_current_style = &this->_default_style;
    bool _has_hover_style = false;

    std::function<void ()> _init_debug_information_callback; /**< function to call for debug information initialisation */

    /**
     * default debug information initialisation
     */
    void default_init_debug_information();

    /**
     * Constructor
     *
     * @param type name of drawable subclass
     * @param parent_position global position of parent
     * @param position local position inside parent drawable
     * @param init_debug_information_callback function to call for debug information initialisation
     */
    Drawable(std::string type, Position parent_position = {0,0}, Position position = {0,0}, std::function<void ()> init_debug_information_callback = nullptr);

    /**
     * vector of callbacks for recalculation
     */
    std::vector<std::function<void(Drawable *)>> _recalculation_callbacks;

    /**
     * function to call after current_style is set
     */
    virtual void hook_set_current_style(Style *style);

public:
    const std::string _type;
    Style _default_style;
    Style _hover_style;

    virtual ~Drawable() = default;

    /**
     * getter for _parent
     * @return parent
     */
    Drawable *parent();


    /**
     * getter for the list of children
     * @param reversed flag to determine whether the list should be returned in reversed order
     * @return list of children
     */
    std::list<Drawable *> children(bool reversed = false);
    const std::list<Drawable *> children(bool reversed = false) const;


    /**
     * add a given drawable as child
     * @param child drawable to add as child
     */
    void add_child(Drawable *child);


    /**
     * add a vector of drawables as children
     * @params children drawables to adda s children
     */
    void add_children(std::vector<Drawable *> children);


    /**
     * find the first drawable DFS that hols a given condition
     * @param f condition
     * @return first drawable that holds for the given condition
     */
    Drawable *find_first(std::function<bool (Drawable *)> f);

    /**
     * find the first drawable DFS reversed that hols a given condition
     * @param f condition
     * @return first drawable that holds for the given condition
     */
    Drawable *find_first_bottom_up(std::function<bool (Drawable *)> f);

    /**
     * create list of Drawables by filtering this subtree
     * @param f filter to apply
     * @return list of filtered drawables
     */
    std::vector<Drawable *> filter(std::function<bool (Drawable *)> f);
    std::vector<const Drawable *> filter(std::function<bool (const Drawable *)> f) const;

    /**
     * apply a function recursively to this and all children
     * @param f function to apply
     * @param reversed flag that determines the order of child processing. If True, the list of
     *   children gets reversed before applying f
     */
    void map(std::function<void (Drawable *)> f, bool reversed = false);

    /**
     * apply a function recursively to this and all children from bottom to topof the tree
     * @param f function to apply
     * @param reversed flag that determines the order of child processing. If True, the list of
     *   children gets reversed before applying f
     */
    void bottom_up_map(std::function<void (Drawable *)> f, bool reversed = false);

    /**
     * apply a function recursively to this and all children propagating a value
     * @param f function to apply
     * @param value initial value
     * @param reversed flag to determine the order of child processing. If true, the list of
     *   children gets reversed before applying f
     */
    template<typename R>
    void reduce(std::function<R (Drawable *, R)> f, R value, bool reversed = false) {
        R this_value = f(this, value);
        for (Drawable *d: this->children(reversed)) {
            d->reduce(f, this_value, reversed);
        }
    }
    template<typename R>
    void reduce(std::function<R (const Drawable *, R)> f, R value, bool reversed = false) const {
        R this_value = f(this, value);
        for (const Drawable *d: this->children(reversed)) {
            d->reduce(f, this_value, reversed);
        }
    }

    /**
     * apply a function recursively reversed, from bottom to top of the tree aggregating the return value
     * @param f function to apply
     * @param value initial value
     * @param aggregate function to aggregate return values from all children
     * @param reversed flag to determine the order of child processing. If true, the list of
     *  children gets reversed before applying f
     * @returns last aggregated propagation value
     */
    template<typename R>
    R bottom_up_reduce(std::function<R (Drawable *, R)> f, R value, std::function<R (std::vector<R>)> aggregate, bool reversed = false) {
        if (this->_children.empty()) {
            return f(this, value);
        }
        std::vector<R> vec;
        for (const Drawable *d: this->children(reversed)) {
            vec.push_back(d->reduce(f, value, aggregate, reversed));
        }
        return f(this, aggregate(vec));
    }


    /**
     * initialise debug information
     */
    void init_debug_information();

    /**
     * Offset position.
     * This also updates the absolute position of all children
     * @param position Position to add to current position
     */
    void move(Position position) override;

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
     * draw this Objects border. If it should have one. gets called by render()
     *
     * @param renderer
     *   renderer to draw on
     * @param position
     *   global offset in window
     */
    void draw_border(SDL_Renderer *renderer, Position position) const;

    /**
     * change the style to use for rendering
     *
     * @param style
     *   style to use
     */
    void set_current_style(Style *style);

    bool has_hover_style();

    /**
     * add a callback function for data binding
     * @param callback callback function that gets executed every tick
     */
    void add_recalculation_callback(std::function<void(Drawable *)> callback);

    /**
     * recalculate attributes of this drawable by calling all of the recalculation callbacks
     */
    void recalculate();

    void show();

    void hide();

    bool is_hidden() const;
};

class NullDrawable : public Drawable {
public:
    ~NullDrawable() = default;
    NullDrawable() : Drawable("Null") {}
    virtual void draw(SDL_Renderer *renderer, Position position) const {
        (void) renderer;
        (void) position;
    }
    void recalculate() {}
};
}
