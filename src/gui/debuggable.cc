#include <gui/debuggable.h>
#include <gui/drawable.h>

using namespace SDL_GUI;

Debuggable::Debuggable() {
    this->_draw_debug_information = std::bind(&Debuggable::default_draw_debug_information, this,
                                              std::placeholders::_1, std::placeholders::_2);
}

Debuggable::~Debuggable() {
    for (Drawable *d: this->_debug_information) {
        delete d;
    }
}

void Debuggable::default_draw_debug_information(SDL_Renderer *renderer, Position position) const {
    if (not this->_debug_information_shown) {
        return;
    }
    for (Drawable *d: this->_debug_information) {
        d->recalculate();
        d->draw(renderer, position + d->position());
    }
}

void Debuggable::draw_debug_information(SDL_Renderer *renderer, Position position) const {
    this->_draw_debug_information(renderer, position);
}

void Debuggable::set_debug_information_shown(bool debug_information_shown) {
    this->_debug_information_shown = debug_information_shown;
}

void Debuggable::show_debug_information() {
    this->_debug_information_shown = true;
}

void Debuggable::hide_debug_information() {
    this->_debug_information_shown = false;
}
