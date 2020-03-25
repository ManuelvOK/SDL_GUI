#include <views/interface_view.h>

#include <iostream>
#include <tuple>

#include <gui/primitives/rect.h>
#include <gui/primitives/text.h>

using namespace SDL_GUI;

InterfaceView::InterfaceView(SDL_Renderer *renderer, const InterfaceModel *interface_model) : _renderer(renderer), _interface_model(interface_model) {
    this->init();
}


bool InterfaceView::init() {
    return true;
}

void InterfaceView::deinit() {}

void InterfaceView::update() {
}

void InterfaceView::render() {
    SDL_SetRenderDrawColor(this->_renderer, 170, 170, 170, 0);
    SDL_RenderClear(this->_renderer);


    SDL_Renderer *renderer = this->_renderer;
    /* draw all drawables recursively */
    SDL_RenderSetClipRect(renderer, NULL);
    SDL_Rect initial_clip_rect = {
        0,
        0,
        static_cast<int>(this->_interface_model->window_width()),
        static_cast<int>(this->_interface_model->window_height())
    };
    this->_interface_model->drawable_tree()->reduce<std::tuple<Position, Position, SDL_Rect, bool>>([renderer](const Drawable *drawable, auto v) {
            Position scroll_position = std::get<1>(v);
            Position position = std::get<0>(v) + drawable->position();
            Position position_with_scrolling = position + scroll_position;
            SDL_Rect parent_clip_rect = std::get<2>(v);
            bool hidden = std::get<3>(v);
            if (hidden || drawable->is_hidden()) {
                std::get<3>(v) = true;
                return v;
            }
            SDL_RenderSetClipRect(renderer, &parent_clip_rect);
            //std::cout << "rendering " << drawable->_type << " at position " << position_with_scrolling << "\n";
            drawable->draw(renderer, position_with_scrolling);
            drawable->draw_border(renderer, position_with_scrolling);
            /* calculate new clip rect */
            int new_x = std::max(parent_clip_rect.x, position_with_scrolling._x);
            int new_y = std::max(parent_clip_rect.y, position_with_scrolling._y);
            int new_width = std::min(parent_clip_rect.x + parent_clip_rect.w, static_cast<int>(new_x + drawable->width())) - new_x;
            int new_height = std::min(parent_clip_rect.y + parent_clip_rect.h, static_cast<int>(new_y + drawable->height())) - new_y;
            parent_clip_rect = {new_x, new_y, new_width, new_height};
            return std::make_tuple(position, scroll_position + drawable->scroll_position(), parent_clip_rect, false);
        }, std::make_tuple(Position{0,0}, Position{0,0}, initial_clip_rect, false));

    SDL_RenderPresent(this->_renderer);
}
