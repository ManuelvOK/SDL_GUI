#include <views/interface_view.h>

#include <iostream>

#include <gui/primitives/rect.h>
#include <gui/primitives/text.h>

InterfaceView::InterfaceView(SDL_Renderer *renderer) : _renderer(renderer) {
    this->init();
}

void InterfaceView::set_mouse_input_model(const MouseInputModel *mouse_input_model) {
    this->_mouse_input_model = mouse_input_model;
}

bool InterfaceView::init() {
    /* init font */
    this->_font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 12);
    if (!this->_font) {
        std::cerr << "TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    /* set up frames n stuff */
    Rect *rect = new Rect({0, 0}, 1600, 900);
    rect->_default_style._color = {177, 177, 177};
    rect->_default_style._border_color = {100, 100, 100};
    rect->_default_style._border = true;
    rect->_hover_style = rect->_default_style;
    this->_draw_root = rect;

    Text *text = new Text("Example Text 1", this->_font);
    rect->add_child(text);
    text = new Text("Example Text 2", this->_font);
    text->set_position({200, 50});
    rect->add_child(text);

    return true;
}

void InterfaceView::deinit() {}

void InterfaceView::update() {
    Position current_position = this->_mouse_input_model->current_position();
    this->_draw_root->map([current_position](Drawable *d){
            if (d->is_inside(current_position)) {
                d->set_current_style(&d->_hover_style);
            } else {
                d->set_current_style(&d->_default_style);
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
