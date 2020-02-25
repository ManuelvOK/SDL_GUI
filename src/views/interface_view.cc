#include <views/interface_view.h>

#include <iostream>

#include <gui/primitives/rect.h>
#include <gui/primitives/text.h>

using namespace SDL_GUI;

InterfaceView::InterfaceView(SDL_Renderer *renderer, const InterfaceModel *interface_model) : _renderer(renderer), _interface_model(interface_model) {
    this->init();
}


bool InterfaceView::init() {


    return true;

    /* set up frames n stuff */
    //Rect *rect = new Rect({0, 0}, 1600, 900);
    //rect->_default_style._color = {177, 177, 177};
    //rect->_default_style._border_color = {100, 100, 100};
    //rect->_default_style._border = true;
    //rect->_hover_style = rect->_default_style;
    //this->_draw_root = rect;

    //Text *text = new Text("Example Text 1", this->_font);
    //rect->add_child(text);
    //text = new Text("Example Text 2", this->_font);
    //text->set_position({200, 50});
    //rect->add_child(text);

    //return true;
}

void InterfaceView::deinit() {}

void InterfaceView::update() {
}

void InterfaceView::render() {
    SDL_SetRenderDrawColor(this->_renderer, 170, 170, 170, 0);
    SDL_RenderClear(this->_renderer);


    SDL_Renderer *renderer = this->_renderer;
    /* draw all drawables recursively */
    this->_interface_model->drawable_tree()->reduce<Position>([renderer](const Drawable *drawable, Position parent_position) {
            Position position = parent_position + drawable->position();
            drawable->draw(renderer, position);
            return position + drawable->scroll_position();
        }, {0,0});
//    this->draw(renderer, position);
//    for (Drawable *child: this->_children) {
//        if (child == nullptr) {
//            continue;
//        }
//        child->render(renderer, position);
//    }

    SDL_RenderPresent(this->_renderer);
}
