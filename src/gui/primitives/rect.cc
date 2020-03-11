#include <gui/primitives/rect.h>

using namespace SDL_GUI;

Rect::Rect(Position position, unsigned width, unsigned height) : Drawable("Rect", position) {
    this->_width = width;
    this->_height = height;
}

void Rect::draw(SDL_Renderer *renderer, Position position) const {
    SDL_Rect r = {position._x,
                  position._y,
                  static_cast<int>(this->_width),
                  static_cast<int>(this->_height)};

    if (this->_current_style->_has_background) {
        this->_current_style->_color.activate(renderer);
        SDL_RenderFillRect(renderer, &r);
    }

    /* draw border */
    if (not this->_current_style->_has_border) {
        return;
    }
    this->_current_style->_border_color.activate(renderer);
    SDL_RenderDrawRect(renderer, &r);
    /* since the drawn rect does not include the lower right point,
     * we have to draw it manually */
    SDL_RenderDrawPoint(renderer, r.x + r.w - 1, r.y + r.h - 1);
}
