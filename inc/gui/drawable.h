#pragma once

#include <functional>
#include <list>

#include <SDL2/SDL.h>

#include <gui/attributable.h>
#include <gui/position.h>
#include <gui/positionable.h>
#include <gui/style.h>

class Drawable : public Positionable, public Attributable {
protected:
    Drawable *_parent = nullptr;
    std::list<Drawable *> _children;
    std::list<Drawable *> _children_reversed;

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
     * draw this Object. gets called by render()
     *
     * @param renderer
     *   renderer to draw on
     * @param position
     *   global offset in window
     */
    virtual void draw(SDL_Renderer *renderer, Position position) const = 0;
public:
    Style _default_style;
    Style _hover_style;
    Style *_current_style = &this->_default_style;

    /**
     * getter for the list of children
     *
     * @param reversed
     *   flag to determine if the list should be returned reversed
     * @returns
     *   list of children
     */
    std::list<Drawable *> children(bool reversed = false);

    /**
     * apply a function recursively to this and all children
     *
     * @param f
     *   function to apply
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    void map(std::function<void (Drawable *)> f, bool reversed = false);

    /**
     * apply a function recursively to this and all children from bottom to top of the tree
     *
     * @param f
     *   function to apply
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    void bottom_up_map(std::function<void (Drawable *)> f, bool reversed = false);

    /**
     * apply a function recursively to this and all children propagating a value
     *
     * @param f
     *   function to apply
     * @param value
     *   initial value
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     */
    template<typename T>
    void reduce(std::function<T (Drawable *, T)> f, T value, bool reversed = false);

    /**
     * apply a function recursively reversed, from bottom to top of the tree aggregating the return value
     *
     * @param f
     *   function to apply
     * @param value
     *   initial value
     * @param aggregate
     *   function to aggregate return values from all children
     * @param reversed
     *   flag to determine the order of child processing. If true, the list of childs get
     *   reversed before applying f
     * @returns
     *   last aggregated propagation value
     */
    template<typename T>
    T bottom_up_reduce(std::function<T (Drawable *, T)> f, T value, std::function<T (std::vector<T>)> aggregate, bool reversed = false);

    /**
     * draw this and all of its childs
     *
     * @param renderer
     *   renderer to draw on
     * @param parent_position
     *   global offset of parent
     */
    void render(SDL_Renderer *renderer, Position parent_position = {0,0}) const;

    /**
     * Find first Child that holds a given attribute
     *
     * @param attribute
     *   attribute to search for
     * @returns
     *   first found Drawable that holds the given attribute. nullptr if no such object exists.
     */
    Drawable *find_first_with_attribute(std::string attribute);

    /**
     * Find all Childs that hold a given attribute
     *
     * @param attribute
     *   attribute to search for
     * @returns
     *   List of Objects that hold the given attribute.
     */
    std::vector<Drawable *> find_all_with_attribute(std::string attribute);

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
    void add_child(Drawable *child);
};
