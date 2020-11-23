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

/**
 * This function is used to recursively instantiate all the Plugins. This special case has an empty
 * template list and results in an empty tuple. This is the last recursion.
 */
template <typename ... Ts>
typename std::enable_if<(sizeof...(Ts) == 0), std::tuple<Ts...>>::type
create_plugins(ApplicationBase *application, int argc, char *argv[]) {
    (void)application;
    (void)argc;
    (void)argv;
    return std::make_tuple();
}


/**
 * This function is used to recursively instantiate all the Plugins. The first given template
 * parameter gets instantiated with access to all the template parameters after it.
 */
template <typename T, typename ... Ts>
std::tuple<T, Ts...> create_plugins(ApplicationBase *application, int argc, char *argv[]) {
    std::tuple<Ts...> previous = create_plugins<Ts...>(application, argc, argv);
    T current = T();
    current.init(application, previous, argc, argv);
    return std::tuple_cat(std::make_tuple(current), previous);
}



class ApplicationBase {
protected:
    std::string _application_title = "";            /**< title string of the Application */
    std::vector<ModelBase *> _model_list;           /**< list of Models */
    std::vector<ViewBase *> _view_list;             /**< list of views */
    std::vector<ControllerBase *> _controller_list; /**< list of controllers */
    SDL_Window *_window = nullptr;                  /**< window to render in */
    SDL_Renderer *_renderer = nullptr;              /**< renderer to render on */
    unsigned _window_width;                         /**< width of window */
    unsigned _window_height;                        /**< height of window */
    int _fps = 60;                                  /**< number of frames per second */


    /**
     * initialise everything concerning SDL
     */
    static void init_SDL();

    /**
     * initialise the window
     */
    static SDL_Window *init_window(std::string title, unsigned width, unsigned height);

    /**
     * initialise the renderer
     */
    static SDL_Renderer *init_renderer(SDL_Window *window);

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
                    unsigned window_height = 1080);

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

        /* properly destroy renderer and window */
        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_window);

        /* properly shut down SDL */
        TTF_Quit();
        SDL_Quit();
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
        typename std::tuple<Ts...> _plugins;

    public:
        /**
         * Constructor
         * @param application_title title string for the application
         */
        Application(std::string application_title, int argc, char *argv[],
                unsigned window_width = 1920, unsigned window_height = 1080)
            : ApplicationBase(application_title, window_width, window_height) {
                this->_plugins = create_plugins<Ts...>(this, argc, argv);
            }


};
}
