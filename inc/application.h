#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include <controllers/controller_base.h>
#include <controllers/interface_controller.h>
#include <controllers/keyboard_input_controller.h>
#include <models/interface_model.h>
#include <models/keyboard_input_model.h>
#include <models/model_base.h>
#include <models/mouse_input_model.h>
#include <views/interface_view.h>
#include <views/view_base.h>

class Application {
    std::string _application_title = "";

    std::vector<ModelBase *> _model_list;
    std::vector<ViewBase *> _view_list;
    std::vector<ControllerBase *> _controller_list;
    const KeyboardInputModel *_keyboard_input_model = nullptr;
    const MouseInputModel *_mouse_input_model = nullptr;

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
