#include <gui/primitives/rect.h>

using namespace SDL_GUI;

Rect::Rect(Position parent_position, Position position, unsigned width, unsigned height) : Drawable("Rect", parent_position, position) {
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
}
