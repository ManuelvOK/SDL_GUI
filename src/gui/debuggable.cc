#include <gui/debuggable.h>
#include <gui/drawable.h>

using namespace SDL_GUI;

Debuggable::Debuggable() {
    this->_draw_debug_information = std::bind(&Debuggable::default_draw_debug_information, this,
                                              std::placeholders::_1, std::placeholders::_2,
                                              std::placeholders::_3);
}

Debuggable::~Debuggable() {
    if (this->_debug_information) {
        delete this->_debug_information;
    }
}

void Debuggable::default_draw_debug_information(SDL_Renderer *renderer, Position position,
                                                SDL_Rect parent_clip_rect) const {
    if (not this->_debug_information) {
        return;
    }
    if (not this->_debug_information_shown) {
        return;
    }
    this->_debug_information->recalculate();
    this->_debug_information->render(renderer, position, parent_clip_rect, false, true);
}

void Debuggable::draw_debug_information(SDL_Renderer *renderer, Position position,
                                        SDL_Rect parent_clip_rect) const {
    this->_draw_debug_information(renderer, position, parent_clip_rect);
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
