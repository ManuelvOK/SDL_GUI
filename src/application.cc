#include <application.h>

#include <iostream>
#include <chrono>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace SDL_GUI;

Application::Application(std::string application_title) :
    _application_title(application_title) {}

Application::~Application() {
    for (ModelBase *model: this->_model_list) {
        delete model;
    }
    for (ViewBase *view: this->_view_list) {
        delete view;
    }
    for (ControllerBase *controller: this->_controller_list) {
        delete controller;
    }
}


void Application::init() {
    this->init_SDL();
    this->init_window();
    this->init_renderer();

    this->init_MVCs();
}

void Application::init_SDL() {
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    if (0 != TTF_Init()) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    atexit(this->quit_SDL);
}

void Application::init_window() {
    /* init window */
    /* TODO: get rid of magic number */
    this->_window = SDL_CreateWindow(this->_application_title.c_str(), 0, 0, 640, 480,
            SDL_WINDOW_RESIZABLE);
    if (this->_window == nullptr) {
        std::cerr << "unable to create window: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    on_exit(this->exit_SDL_DestroyWindow, this->_window);
}

void Application::init_renderer() {
    /* init renderer */
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC);
    if (this->_renderer == nullptr) {
        std::cerr << "unable to create renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    on_exit(this->exit_SDL_DestroyRenderer, this->_renderer);
}

void Application::quit_SDL() {
    TTF_Quit();
    SDL_Quit();
}

void Application::exit_SDL_DestroyWindow(int status, void *window) {
    (void) status;
    SDL_DestroyWindow(static_cast<SDL_Window *>(window));
}

void Application::exit_SDL_DestroyRenderer(int status, void *renderer) {
    (void) status;
    SDL_DestroyRenderer(static_cast<SDL_Renderer *>(renderer));
}

inline std::chrono::high_resolution_clock::duration t_sys() {
    return std::chrono::high_resolution_clock::now().time_since_epoch();
}

void Application::run() {
    this->init();

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
        this->update_running();
    }
    this->deinit();
}

void Application::deinit() {}

void Application::update_controllers() {
    for (ControllerBase *controller: this->_controller_list) {
        controller->update();
    }
}

void Application::update_views() {
    for (ViewBase *view: this->_view_list) {
        view->update();
    }
}

void Application::render_views() {
    for (ViewBase *view: this->_view_list) {
        view->render();
    }
}
