#include <application.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <chrono>
#include <algorithm>

/**
 * Initialise SDL for video output
 */
void init_SDL();

void quit_SDL();

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

bool Application::init() {
    this->init_SDL();

    /* init window */
    /* TODO: get rid of magic number */
    this->_window = SDL_CreateWindow(this->_application_title.c_str(), 0, 0, 640, 480,
            SDL_WINDOW_RESIZABLE);
    if (this->_window == nullptr) {
        std::cerr << "unable to create window: " << SDL_GetError() << std::endl;
        return false;
    }
    on_exit(this->exit_SDL_DestroyWindow, this->_window);

    /* init renderer */
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC);
    if (this->_renderer == nullptr) {
        std::cerr << "unable to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    on_exit(this->exit_SDL_DestroyRenderer, this->_renderer);

    /* init interface model */
    InterfaceModel *interface_model = new InterfaceModel();
    this->_model_list.push_back(interface_model);

    /* init interface controller */
    InterfaceController *interface_controller = new InterfaceController();
    this->_controller_list.push_back(interface_controller);

    /* init interface view */
    InterfaceView *interface_view = new InterfaceView(this->_renderer);
    interface_view->set_model(interface_model);
    this->_view_list.push_back(interface_view);

    /* init keyboard input controller */
    KeyboardInputModel *keyboard_input_model = new KeyboardInputModel();
    this->_model_list.push_back(keyboard_input_model);
    this->_keyboard_input_model = keyboard_input_model;

    /* init keyboard input controller */
    KeyboardInputController *keyboard_input_controller = new KeyboardInputController();
    keyboard_input_controller->set_model(keyboard_input_model);
    this->_controller_list.push_back(keyboard_input_controller);

    /* init keyboard input controller */
    MouseInputModel *mouse_input_model = new MouseInputModel();
    this->_model_list.push_back(mouse_input_model);
    this->_mouse_input_model = mouse_input_model;

    /* init mouse input controller */
    MouseInputController *mouse_input_controller = new MouseInputController();
    mouse_input_controller->set_model(mouse_input_model);
    this->_controller_list.push_back(mouse_input_controller);

    return true;
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
    if (not this->init()) {
        return;
    }

    using duration_t = std::chrono::high_resolution_clock::duration;
    unsigned logic_count = 0;
    unsigned render_count = 0;

    /* TODO: get rid of magic number */
    const duration_t dt = std::chrono::microseconds(1000000 / 60);
    duration_t t_app = t_sys();
    duration_t t_logic = t_app - dt;
    while (this->_is_running) {
        while(t_app - t_logic >= dt) {
            logic_count++;
            t_logic += dt;

            this->update_controllers();
            this->update_views();
            this->manage_views_and_controllers();
        }

        t_app = t_sys();
        /* render */
        render_count ++;
        this->render_views();

        if (this->_keyboard_input_model->is_pressed(KeyboardInputModel::Key::QUIT)) {
            this->_is_running = false;
        }
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
        if (view->has_model()) {
            view->update();
        }
    }
}

void Application::render_views() {
    for (ViewBase *view: this->_view_list) {
        if (view->has_model()) {
            view->render();
        }
    }
}

void Application::manage_views_and_controllers() {
    std::remove_if(
            this->_view_list.begin(), this->_view_list.end(),
            [](ViewBase *view) { return !view->has_model(); });
}
