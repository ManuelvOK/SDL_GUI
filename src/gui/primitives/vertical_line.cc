#include <gui/primitives/vertical_line.h>

using namespace SDL_GUI;

void VerticalLine::draw(SDL_Renderer *renderer, Position position) const {
    this->_current_style->_color.activate(renderer);
    SDL_RenderDrawLine(renderer, position._x, position._y, position._x, position._y + this->_height);
}
