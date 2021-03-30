#include <gui/rgb.h>

using namespace SDL_GUI;

RGB::RGB(std::string color) {
    if (this->_predefinitions.find(color) == this->_predefinitions.end()) {
        return;
    }
    std::array<unsigned char, 4> rgb_values = this->_predefinitions.at(color);
    this->_r = rgb_values[0];
    this->_g = rgb_values[1];
    this->_b = rgb_values[2];
    this->_a = rgb_values[3];
}

RGB::operator SDL_Color() const {
    return SDL_Color{this->_r, this->_g, this->_b, this->_a};
}

RGB &RGB::operator=(const RGB &rgb) {
    this->_r = rgb._r;
    this->_g = rgb._g;
    this->_b = rgb._b;
    this->_a = rgb._a;
}

void RGB::activate(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, this->_r, this->_g, this->_b, this->_a);
}
