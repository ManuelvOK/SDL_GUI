#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include <controller/controller_base.h>
#include <controller/input_controller.h>
#include <controller/interface_controller.h>
#include <model/input_model.h>
#include <model/interface_model.h>
#include <model/model_base.h>
#include <view/interface_view.h>
#include <view/view_base.h>

class Application {
    std::string _application_title = "";

    std::vector<ModelBase *> _model_list;
    std::vector<ViewBase *> _view_list;
    std::vector<ControllerBase *> _controller_list;
    InterfaceModel *_interface_model = nullptr;
    InterfaceController *_interface_controller = nullptr;
    InterfaceView *_interface_view = nullptr;
    InputModel *_input_model = nullptr;
    InputController *_input_controller = nullptr;

    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;

    bool _is_running = true;

    void init_SDL();
    static void quit_SDL();

    static void exit_SDL_DestroyWindow(int status, void *window);
    static void exit_SDL_DestroyRenderer(int status, void *renderer);
public:
    Application(std::string application_title);
    ~Application();
    bool init();
    void run();
    void deinit();
    void update_controllers();
    void update_views();
    void render_views();
    void manage_views_and_controllers();

};
