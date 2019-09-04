#include <view/interface_view.h>

InterfaceView::InterfaceView(SDL_Renderer *renderer) : _renderer(renderer) {
    this->init();
}

bool InterfaceView::init() {
    /* set up frames n stuff */
    return true;
}

void InterfaceView::deinit() {}

void InterfaceView::update() {}

void InterfaceView::render() {
    /* draw all frames recursively */
    SDL_SetRenderDrawColor(this->_renderer, 170, 170, 170, 0);
    SDL_RenderClear(this->_renderer);
    SDL_RenderPresent(this->_renderer);
}
