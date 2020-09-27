#pragma once

#include <string>
#include <tuple>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "controllers/controller_base.h"
#include "models/model_base.h"
#include "plugins/plugin_base.h"
#include "views/view_base.h"

#include "gui/primitives/texture.h"

namespace SDL_GUI {

class ApplicationBase;
template <typename ... Ts>
typename std::enable_if<(sizeof...(Ts) == 0), std::tuple<Ts...>>::type
create_plugins(ApplicationBase *application) {
    (void)application;
    return std::make_tuple();
}

template <typename T, typename ... Ts>
std::tuple<Ts..., T> create_plugins(ApplicationBase *application) {
    std::tuple<Ts...> previous = create_plugins<Ts...>(application);
    T current = T();
    current.init(application, previous);
    return std::tuple_cat(previous, std::make_tuple(current));
}

// https://stackoverflow.com/questions/17178075/how-do-i-reverse-the-order-of-element-types-in-a-tuple-type/17178399#17178399
template <typename... Ts>
struct tuple_reverse;

template <>
struct tuple_reverse<std::tuple<>>
{
    using type = std::tuple<>;
};

template <typename T, typename... Ts>
struct tuple_reverse<std::tuple<T, Ts...>>
{
  using head = std::tuple<T>;
  using tail = typename tuple_reverse<std::tuple<Ts...>>::type;

  using type = decltype(std::tuple_cat(std::declval<tail>(), std::declval<head>()));
};




class ApplicationBase {
protected:
    /**
     * title string of the Application
     */
    std::string _application_title = "";
    /**
     * list of Models
     */
    std::vector<ModelBase *> _model_list;

    /**
     * list of views
     */
    std::vector<ViewBase *> _view_list;

    /**
     * list of controllers
     */
    std::vector<ControllerBase *> _controller_list;

    /**
     * window to render in
     */
    SDL_Window *_window = nullptr;

    /**
     * renderer to render on
     */
    SDL_Renderer *_renderer = nullptr;

    unsigned _window_width;

    unsigned _window_height;

    /**
     * number of frames per second
     */
    int _fps = 60;

    /**
        * trigger proper destruction of everything concerning SDL
        */
    static void quit_SDL() {
        TTF_Quit();
        SDL_Quit();
    }

    /**
        * proper destruction of the SDL Window
        * @param status TODO: what is this?
        * @param window Pointer to the SDL Window to destroy
        */
    static void exit_SDL_DestroyWindow(int status, void *window) {
        (void) status;
        SDL_DestroyWindow(static_cast<SDL_Window *>(window));
    }

    /**
        * proper destruction of the SDL Renderer
        * @param status TODO: what is this?
        * @param renderer Pointer to the SDL Renderer to destroy
        */
    static void exit_SDL_DestroyRenderer(int status, void *renderer) {
        (void) status;
        SDL_DestroyRenderer(static_cast<SDL_Renderer *>(renderer));
    }


    /**
        * initialise everything concerning SDL
        */
    void init_SDL() {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        if (0 != TTF_Init()) {
            std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        atexit(quit_SDL);
    }

    /**
        * initialise the window
        */
    SDL_Window *init_window(std::string title, unsigned width, unsigned height) {
        /* init window */
        /* TODO: get rid of magic number */
        SDL_Window *window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, SDL_WINDOW_RESIZABLE);
        if (window == nullptr) {
            std::cerr << "unable to create window: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        on_exit(exit_SDL_DestroyWindow, window);
        return window;
    }

    /**
        * initialise the renderer
        */
    SDL_Renderer *init_renderer(SDL_Window *window) {
        /* init renderer */
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            std::cerr << "unable to create renderer: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        on_exit(exit_SDL_DestroyRenderer, renderer);
        return renderer;
    }


    /**
     * do further initialisation in derived classes
     */
    virtual void init_this() {}

    /**
     * deinitialise application
     * Currently this function does nothing
     */
    void deinit() {}

    /**
     * trigger update on all the existing controllers
     */
    void update_controllers();

    /**
     * trigger update on all the existing views that have a related model
     */
    void update_views();

    /**
     * trigger rendering on all the existing views that have a related model
     */
    void render_views();

    /**
     * Constructor
     * @param application_title title string for the application
     */
    ApplicationBase(std::string application_title, unsigned window_width = 1920,
                    unsigned window_height = 1080)
        : _application_title(application_title), _window_width(window_width),
          _window_height(window_height) {
        init_SDL();
        this->_window = init_window(application_title, window_width, window_height);
        this->_renderer = init_renderer(this->_window);
    }

    /**
     * Destructor
     */
    ~ApplicationBase() {
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
    }


public:

    /**
     * flag that determines whether this application should continue running
     */
    bool _is_running = true;

    /**
       * run applicatoin
     * This starts the main loop that updates all the controllers and views and renders.
     */
    void run();

    SDL_Window *window() {
        return this->_window;
    }

    SDL_Renderer *renderer() {
        return this->_renderer;
    }

    unsigned window_width() {
        return this->_window_width;
    }

    unsigned window_height() {
        return this->_window_height;
    }

    void add_model(ModelBase *model) {
        this->_model_list.push_back(model);
    }

    void add_controller(ControllerBase *controller) {
        this->_controller_list.push_back(controller);
    }

    void add_view(ViewBase *view) {
        this->_view_list.push_back(view);
    }

};

template<typename ... Ts>
class Application : public ApplicationBase {
protected:
    /**
     * list of Plugins
     */
    //std::tuple<Ts...> _plugins;
    typename tuple_reverse<std::tuple<Ts...>>::type _plugins;

public:
    /**
     * Constructor
     * @param application_title title string for the application
     */
    Application(std::string application_title, unsigned window_width = 1920,
                unsigned window_height = 1080)
        : ApplicationBase(application_title, window_width, window_height) {
        this->_plugins = create_plugins<Ts...>(this);
    }


};
}
