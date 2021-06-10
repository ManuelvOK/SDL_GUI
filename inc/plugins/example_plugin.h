#pragma once

#include <map>
#include <sstream>

#include <SDL2/SDL.h>

#include <application.h>

#include <controllers/controller_base.h>
#include <plugins/plugin_base.h>
#include <plugins/default_plugin.h>

#include <gui/primitives/text.h>
#include <gui/primitives/texture.h>
#include <gui/primitives/line.h>
#include <gui/primitives/polygon.h>

namespace SDL_GUI {

/**
 * Abstraction for all possible inputs this plugin handles
 * For this Example its only important to close the application
 */
enum class ExampleInputKey {
    QUIT,
    DEBUG,
};

enum class ExampleInputState {
    ALL,
};

/**
 * Keyboard input config.
 * Keypresses of `[ESC]` and `[Q]` both will result in quitting the application
 */
static const std::map<ExampleInputState,
                      std::map<std::set<SDL_Scancode>,
                               std::map<SDL_Scancode, ExampleInputKey>>>
example_keyboard_input_config = {
    {ExampleInputState::ALL, {
        {{}, {
            {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
            {SDL_SCANCODE_ESCAPE, ExampleInputKey::QUIT},
        }},
        {{SDL_SCANCODE_LSHIFT}, {
            {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
            {SDL_SCANCODE_D, ExampleInputKey::DEBUG},
        }},
        {{SDL_SCANCODE_RSHIFT}, {
            {SDL_SCANCODE_Q, ExampleInputKey::QUIT},
            {SDL_SCANCODE_D, ExampleInputKey::DEBUG},
        }},
    }},
};

/**
 * Window event config.
 * This could be used to react to changes in the window size.
 */
static const std::map<SDL_WindowEventID, ExampleInputKey> example_window_event_config;

/**
 * Mouse input config
 * This could be used to react to mouse clicks or movements or scrolling.
 */
static const std::map<ExampleInputState,
                      std::map<std::set<SDL_Scancode>,
                               std::map<Uint8, ExampleInputKey>>> example_mouse_input_config;

/** Plugins controller */
class ExampleController : public ControllerBase {
    ApplicationBase *_application;              /**< The application */
    InputModel<ExampleInputKey, ExampleInputState> *_input_model;  /**< The applications input model */
    InterfaceModel *_interface_model;
public:
    /**
     * Constructor
     * @param application The application
     * @param input_model The applications input model
     */
    ExampleController(ApplicationBase *application,
                      InputModel<ExampleInputKey, ExampleInputState> *input_model,
                      InterfaceModel *interface_model)
        : _application(application), _input_model(input_model),
          _interface_model(interface_model) {}

    /**
     * Check if application should quit
     */
    virtual void update() {
        if (this->_input_model->is_pressed(ExampleInputKey::QUIT)) {
            this->_application->_is_running = false;
        }
        if (this->_input_model->is_down(ExampleInputKey::DEBUG)) {
            this->_interface_model->toggle_debug_information_drawn();
        }
    }
};

/** The Plugin we use to show what this library can do */
class ExamplePlugin: public PluginBase {
    InterfaceModel *_interface_model;
public:
    /** Constructor */
    ExamplePlugin(CommandLine *command_line): PluginBase("Example Plugin", command_line) {}

    /**
     * Create all the needed Models, Controllers and Views
     * @tparam Ts List of already instantiated plugin types
     * @param app The application
     * @param plugins tuple of other plugins
     */
    template <typename ... Ts>
    void init(ApplicationBase *app, std::tuple<Ts...> *plugins) {
        (void)app;

        if (app->is_headless()) {
            return;
        }

        /* Models */
        InputModel<ExampleInputKey, ExampleInputState> *input_model =
            new InputModel<ExampleInputKey, ExampleInputState>(ExampleInputState::ALL);
        app->add_model(input_model);

        /* Controllers */
        InputController<ExampleInputKey, ExampleInputState> *input_controller =
            new InputController<ExampleInputKey, ExampleInputState>(
                    input_model, example_keyboard_input_config, example_window_event_config,
                    example_mouse_input_config,
                    ExampleInputKey::QUIT);
        app->add_controller(input_controller);

        DefaultPlugin &default_plugin = std::get<DefaultPlugin>(*plugins);
        this->_interface_model = default_plugin.interface_model();

        ExampleController *example_controller = new ExampleController(app, input_model,
                                                                      this->_interface_model);
        app->add_controller(example_controller);

        /* Add content */

        Drawable *stats = this->_interface_model->find_first_drawable("stats");
        stats->add_recalculation_callback(
            [this, app](Drawable *d) {
                d->remove_all_children();

                std::stringstream ss;
                ss << "fps:   " << app->current_fps();
                Text *t = new Text(this->_interface_model->font(), ss.str());
                t->set_x(5);
                d->add_child(t);

                ss.str("");
                ss << "tps:   " << app->current_tps();
                t = new Text(this->_interface_model->font(), ss.str());
                t->set_x(5);
                t->set_y(13);
                d->add_child(t);

                ss.str("");
                ss << "loops: " << app->current_loops();
                t = new Text(this->_interface_model->font(), ss.str());
                t->set_x(5);
                t->set_y(25);
                d->add_child(t);
            });

        Drawable *image = this->_interface_model->find_first_drawable("image");
        image->_style._border_color = RGB("green");
        image->_style._border_width = 3;
        Texture *t = new Texture("textures/strichmann.png", app->renderer());
        t->set_width(50);
        t->set_height(60);
        image->add_child(t);

        Drawable *line = this->_interface_model->find_first_drawable("line");
        Line *l = new Line({5,5},{95, 20});
        line->add_child(l);

        l = new Line({5,5},{95, 20});
        l->_style._color = RGB("red");
        l->move({0, 20});
        line->add_child(l);

        l = new Line({5,5},{95, 20});
        l->_style._color = RGB("blue");
        l->set_line_width(3);
        l->move({20, 60});
        l->set_end_relative_to_begin({-10, -30});
        line->add_child(l);

        Drawable *polygon = this->_interface_model->find_first_drawable("polygon");
        Polygon *p = new Polygon();
        p->add_point({10, 10});
        p->add_point({15, 30});
        p->add_point({17, 44});
        p->add_point({38, 76});
        p->add_point({70, 20});
        p->add_point({55, 10});
        p->_style._has_background = true;
        p->_style._color = RGB("green");
        p->_style._has_border = true;
        p->_style._border_color = RGB("yellow");
        p->set_line_width(3);
        polygon->add_child(p);
    }
};
}
