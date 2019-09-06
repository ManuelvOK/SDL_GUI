#include <gui/rgb.h>

RGB::operator SDL_Color() const {
    return SDL_Color{this->_r, this->_g, this->_b, this->_a};
}

void RGB::activate(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, this->_r, this->_g, this->_b, this->_a);
}
