#include <gui/primitives/text.h>

using namespace SDL_GUI;

Text::~Text() {
    if (this->_surface != nullptr) {
        SDL_FreeSurface(this->_surface);
    }
}

void Text::create_surface() {
    this->_surface = TTF_RenderText_Blended(this->_font, this->_text.c_str(),
            this->_current_style->_color);
}

void Text::hook_set_current_style(Style *style) {
    (void) style;
    if (this->_surface == nullptr) {
        this->create_surface();
    }
}

void Text::draw(SDL_Renderer *renderer, Position position) const {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, this->_surface);
    SDL_Rect dstrect{position._x, position._y, this->_surface->w, this->_surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
}
