#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "controllers/controller_base.h"
#include "models/keyboard_input_model.h"
#include "models/model_base.h"
#include "models/mouse_input_model.h"
#include "views/view_base.h"
namespace SDL_GUI {
class Application {
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

    /**
     * flag that determines whether this application should continue running
     */
    bool _is_running = true;

    /**
     * number of frames per second
     */
    int _fps = 60;

    /**
     * initialise everything concerning SDL
     */
    void init_SDL();

    /**
     * initialise the window
     */
    void init_window();

    /**
     * initialise the renderer
     */
    void init_renderer();

    /**
     * trigger proper destruction of everything concerning SDL
     */
    static void quit_SDL();

    /**
     * proper destruction of the SDL Window
     * @param status TODO: what is this?
     * @param window Pointer to the SDL Window to destroy
     */
    static void exit_SDL_DestroyWindow(int status, void *window);
    /**
     * proper destruction of the SDL Renderer
     * @param status TODO: what is this?
     * @param renderer Pointer to the SDL Renderer to destroy
     */
    static void exit_SDL_DestroyRenderer(int status, void *renderer);
public:
    /**
     * Constructor
     * @param application_title title string for the application
     */
    Application(std::string application_title);

    /**
     * Destructor
     */
    ~Application();

    /**
     * initialise the application.
     * This initialises SDL, creates all the needed Models, Controllers and Views
     * @return true if initialisation succeeds. Otherwise false
     */
    virtual void init();

    /**
     * run applicatoin
     * This starts the main loop that updates all the controllers and views and renders.
     */
    void run();

    /**
     * deinitialise application
     * Currently this function does nothing
     */
    void deinit();

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
     * filter view list, deleting the ones not having a related model
     */
    void manage_views_and_controllers();

};
}
