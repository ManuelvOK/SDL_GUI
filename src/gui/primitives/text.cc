#include <gui/primitives/text.h>

#include <cassert>

using namespace SDL_GUI;

Text::Text(TTF_Font *font, const std::string text, Position parent_position, Position position)
    : Drawable("Text", parent_position, position), _font(font), _text(text) {
    this->create_surface();
}

Text::~Text() {
    if (this->_surface != nullptr) {
        SDL_FreeSurface(this->_surface);
    }
}

void Text::create_surface() {
    if (this->_surface != nullptr) {
        SDL_FreeSurface(this->_surface);
    }
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

void Text::set_text(const std::string text) {
    this->_text = text;
    this->create_surface();
}

unsigned Text::height() const {
    assert(this->_surface != nullptr);
    return this->_surface->h;
}

unsigned Text::width() const {
    assert(this->_surface != nullptr);
    return this->_surface->w;
}
