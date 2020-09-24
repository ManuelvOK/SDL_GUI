#include <application.h>

#include <iostream>
#include <chrono>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


using namespace SDL_GUI;


inline std::chrono::high_resolution_clock::duration t_sys() {
    return std::chrono::high_resolution_clock::now().time_since_epoch();
}

void ApplicationBase::run() {
    using duration_t = std::chrono::high_resolution_clock::duration;
    unsigned logic_count = 0;
    unsigned render_count = 0;

    const duration_t dt = std::chrono::microseconds(1000000 / this->_fps);
    duration_t time_app = t_sys();
    duration_t time_logic = time_app - dt;
    while (this->_is_running) {
        while(time_app - time_logic >= dt) {
            logic_count++;
            time_logic += dt;

            this->update_controllers();
            this->update_views();
        }

        time_app = t_sys();
        /* render */
        render_count ++;
        this->render_views();
    }
    this->deinit();
}

void ApplicationBase::update_controllers() {
    for (ControllerBase *controller: this->_controller_list) {
        controller->update();
    }
}

void ApplicationBase::update_views() {
    for (ViewBase *view: this->_view_list) {
        view->update();
    }
}

void ApplicationBase::render_views() {
    for (ViewBase *view: this->_view_list) {
        view->render();
    }
}
