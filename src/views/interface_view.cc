#include <views/interface_view.h>

#include <gui/primitives/rect.h>

InterfaceView::InterfaceView(SDL_Renderer *renderer) : _renderer(renderer) {
    this->init();
}

void InterfaceView::set_mouse_input_model(const MouseInputModel *mouse_input_model) {
    this->_mouse_input_model = mouse_input_model;
}

bool InterfaceView::init() {
    /* set up frames n stuff */
    Rect *rect = new Rect({50, 50}, 50, 50);
    rect->_default_style._color = {255, 0, 0};
    rect->_hover_style._color = {255, 0, 0};
    rect->_hover_style._border_color = {0, 0, 0};
    rect->_hover_style._border = true;
    this->_draw_root = rect;
    return true;
}

void InterfaceView::deinit() {}

void InterfaceView::update() {
    Position current_position = this->_mouse_input_model->current_position();
    this->_draw_root->map([current_position](Drawable *d){
            if (d->is_inside(current_position)) {
                d->_current_style = &d->_hover_style;
            } else {
                d->_current_style = &d->_default_style;
            }
        });
}

void InterfaceView::render() {
    SDL_SetRenderDrawColor(this->_renderer, 170, 170, 170, 0);
    SDL_RenderClear(this->_renderer);

    /* draw all drawables recursively */
    this->_draw_root->render(this->_renderer);

    SDL_RenderPresent(this->_renderer);
}
