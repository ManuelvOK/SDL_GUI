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
    bool _has_hover_style = false;

    /**
     * default Contructor
     */
    Drawable(std::string type) : _type(type) {}

    /**
     * Constructor
     *
     * @param position
     *   local position inside parent drawable
     */
    Drawable(std::string type, Position position) : Positionable(position), _type(type) {}

    virtual ~Drawable() = default;

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

    /**
     * check if Position is inside this
     *
     * @param position
     *   Position to check for
     * @returns
     *   True if position is inside. False otherwise.
     */
    virtual bool is_inside(Position position) const;

    void show();

    void hide();

    bool is_hidden() const;

};

class NullDrawable : public Drawable {
public:
    NullDrawable() : Drawable("Null") {}
    virtual void draw(SDL_Renderer *renderer, Position position) const {
        (void) renderer;
        (void) position;
    }
    void recalculate() {}
};
}
