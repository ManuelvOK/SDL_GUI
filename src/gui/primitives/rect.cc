#include <gui/primitives/rect.h>

Rect::Rect(Position position, unsigned width, unsigned height) : Drawable(position) {
    this->_width = width;
    this->_height = height;
}

void Rect::set_color(RGB color) {
    this->_color = color;
}

void Rect::draw(SDL_Renderer *renderer, Position position) const {
    SDL_Rect r = {position._x,
                  position._y,
                  static_cast<int>(this->_width),
                  static_cast<int>(this->_height)};

    this->_color.activate(renderer);
    SDL_RenderFillRect(renderer, &r);

    /* draw border */
    if (not this->_border) {
        return;
    }
    this->_border_color.activate(renderer);
    SDL_RenderDrawRect(renderer, &r);
    /* since the drawn rect does not include the lower right point,
     * we have to draw it manually */
    SDL_RenderDrawPoint(renderer, r.x + r.w - 1, r.y + r.h - 1);

}
