#include <views/interface_view.h>

#include <gui/primitives/rect.h>

InterfaceView::InterfaceView(SDL_Renderer *renderer) : _renderer(renderer) {
    this->init();
}

bool InterfaceView::init() {
    /* set up frames n stuff */
    Rect *rect = new Rect({50, 50}, 50, 50);
    rect->set_color({255, 0, 0});
    this->_draw_root = rect;
    return true;
}

void InterfaceView::deinit() {}

void InterfaceView::update() {}

void InterfaceView::render() {
    SDL_SetRenderDrawColor(this->_renderer, 170, 170, 170, 0);
    SDL_RenderClear(this->_renderer);

    /* draw all drawables recursively */
    this->_draw_root->render(this->_renderer);

    SDL_RenderPresent(this->_renderer);
}
