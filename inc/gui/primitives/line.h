#pragma once

#include "../drawable.h"

namespace SDL_GUI {
/** primitive for drawing a line */
class Line : public Drawable {
protected:
    Position &_begin = this->_position; /**< begin of line (reference to this->_position */
    Positionable _end;                  /**< end of line as an offset related to the begin */
public:
    /**
     * Constructor
     * @param parent_position position of parent drawable
     * @param begin begin of line
     * @param end end of line relative to begin
     */
    Line(Position parent_position = {0,0}, Position begin = {0,0}, Position end = {0,0}) : Drawable("Line", parent_position, begin), _end(end, end - begin) {}

    void draw(SDL_Renderer *renderer, Position position) const override;

    /**
     * setter for _end
     * @param position end relative to begin
     */
    void set_end_relative_to_begin(Position position);

    /**
     * setter for end in relation to the parent drawable
     * @param position end relative to parent drawable
     */
    void set_end_relative_to_parent(Position position);

    /**
     * Setter for begin
     * @param position begin
     */
    void set_begin(Position position);

    /**
     * Getter for _end
     * @return this->_end
     */
    const Position end_relative_to_begin() const;

    /**
     * Getter for _end relative to parent drawable
     * @return end relative to parent drawable
     */
    const Position end_relative_to_parent() const;

    /**
     * Getter for _begin
     * @return this->_begin
     */
    const Position begin() const;
};
}
