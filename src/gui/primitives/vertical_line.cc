#include <gui/primitives/vertical_line.h>

using namespace SDL_GUI;

void VerticalLine::draw(SDL_Renderer *renderer, Position position) const {
    this->_current_style->_color.activate(renderer);
    int begin_x = this->_position._x + position._x;
    int begin_y = this->_position._y + position._y;
    SDL_RenderDrawLine(renderer, begin_x, begin_y, begin_x, begin_y + this->_height);
}
