#include <application.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <controllers/input_controller.h>


using namespace SDL_GUI;


inline std::chrono::high_resolution_clock::duration t_sys() {
    return std::chrono::high_resolution_clock::now().time_since_epoch();
}

ApplicationBase::~ApplicationBase() {
    for (ModelBase *model: this->_model_list) {
        delete model;
    }
    for (ViewBase *view: this->_view_list) {
        delete view;
    }
    for (ControllerBase *controller: this->_controller_list) {
        delete controller;
    }
    for (std::pair<std::string, SDL_Texture *> t: Texture::_textures) {
        SDL_DestroyTexture(t.second);
    }

    /* properly destroy renderer and window */
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);

    /* properly shut down SDL */
    TTF_Quit();
    SDL_Quit();
}

void ApplicationBase::init_SDL() {
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    if (0 != TTF_Init()) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

SDL_Window *ApplicationBase::init_window(std::string title, unsigned width, unsigned height) {
    /* init window at {0,0} */
    SDL_Window *window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cerr << "unable to create window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    return window;
}

SDL_Renderer *ApplicationBase::init_renderer(SDL_Window *window) {
    /* init renderer  for first found rendering device (-1) */
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                                            SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "unable to create renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return renderer;
}

ApplicationBase::ApplicationBase(std::string application_title, unsigned window_width,
                                 unsigned window_height)
    : _application_title(application_title), _window_width(window_width),
      _window_height(window_height) {
    ApplicationBase::init_SDL();
    this->_window = ApplicationBase::init_window(application_title, window_width, window_height);
    this->_renderer = ApplicationBase::init_renderer(this->_window);
}

void ApplicationBase::run() {
    using duration_t = std::chrono::high_resolution_clock::duration;
    std::list<duration_t> ticks;
    std::list<duration_t> frames;

    unsigned logic_count = 0;
    unsigned render_count = 0;

    const duration_t frame_interval = std::chrono::microseconds(1000000 / this->_target_fps);
    const duration_t tick_interval = std::chrono::microseconds(1000000 / this->_target_tps);
    const duration_t one_second = std::chrono::seconds(1);

    duration_t last_tick_time = t_sys();
    duration_t next_tick_time = t_sys();
    duration_t last_frame_time = t_sys();
    duration_t next_frame_time = t_sys();

    duration_t one_second_ago = t_sys() - one_second;

    while (this->_is_running) {
        if (next_tick_time <= t_sys()) {
            read_sdl_events();
            this->update_controllers();
            this->update_views();
            clear_sdl_events();

            logic_count++;
            last_tick_time = t_sys();
            next_tick_time += tick_interval;

            /* update tps stat */
            ticks.push_back(last_tick_time);

            one_second_ago = last_tick_time - one_second;
            while (not ticks.empty() and ticks.front() < one_second_ago) {
                ticks.pop_front();
            }
            this->_current_tps = ticks.size();
        }

        if (next_frame_time <= t_sys()) {
            /* render */
            this->render_views();

            render_count++;
            last_frame_time = t_sys();
            next_frame_time += frame_interval;

            /* update fps stat */
            frames.push_back(last_frame_time);

            one_second_ago = last_frame_time - one_second;
            while (not frames.empty() and frames.front() < one_second_ago) {
                frames.pop_front();
            }
            this->_current_fps = frames.size();
        }
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

SDL_Window *ApplicationBase::window() {
    return this->_window;
}

SDL_Renderer *ApplicationBase::renderer() {
    return this->_renderer;
}

unsigned ApplicationBase::window_width() const {
    return this->_window_width;
}

unsigned ApplicationBase::window_height() const {
    return this->_window_height;
}

unsigned ApplicationBase::target_fps() const {
    return this->_target_fps;
}

unsigned ApplicationBase::current_fps() const {
    return this->_current_fps;
}

unsigned ApplicationBase::target_tps() const {
    return this->_target_tps;
}

unsigned ApplicationBase::current_tps() const {
    return this->_current_tps;
}

void ApplicationBase::add_model(ModelBase *model) {
    this->_model_list.push_back(model);
    std::sort(this->_model_list.begin(), this->_model_list.end(),
        [](ModelBase *a, ModelBase *b){
            return a->_weight < b->_weight;
        }
    );
}

void ApplicationBase::add_controller(ControllerBase *controller) {
    this->_controller_list.push_back(controller);
    std::sort(this->_controller_list.begin(), this->_controller_list.end(),
        [](ControllerBase *a, ControllerBase *b){
            return a->_weight < b->_weight;
        }
    );

}

void ApplicationBase::add_view(ViewBase *view) {
    this->_view_list.push_back(view);
    std::sort(this->_view_list.begin(), this->_view_list.end(),
        [](ViewBase *a, ViewBase *b){
            return a->_weight < b->_weight;
        }
    );
}
