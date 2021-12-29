# Building
## Dependencies
This project has submodules. Make sure you have pulled recursively.

Additionally, the following libraries are required:
 * sdl2
 * sdl2_ttf
 * sdl2_image
 * fontconfig

## Actually Building

`make` builds an example application into `build/SDL_GUI`.
Use `make lib` to build a static library only.

`make lib` builds the following two library files into `build/` that you will have to link statically into your application:

 * libSDL_GUI.a
 * libSDL2_gfx.a

# Using SDL_GUI

## TL;DR
 - Write a plugin like the example one, provided in [inc/plugins/example_plugin.h](inc/plugins/example_plugin.h).
 - Instantiate an `SDL_GUI::Application` with your plugin as another template parameter besides `SDL_GUI::Core` (order matters) in your `main()` (see [src/main.cc](src/main.cc)).
 - call `app.run()`

## An Application and its Plugins
To run a program with this GUI, an `SDL_GUI::Application` object is required. The `SDL_GUI::Application` initialises SDL and will execute the update and render loop. Once the `run()` function of an application is called, it will be executed until the GUI gets exited.
The logic of an application is encapsulated in **plugins**. Plugins are SDL_GUI's modularisation abstraction.
An application holds a set of unique plugins, that are initialised with the application.
The list of used plugins has to be provided as template parameters.
See [src/main.cc](src/main.cc) for the instantiation of an application that consists of the `SDL_GUI::Core` plugin and an additional `SDL_GUI::ExamplePlugin`.
The order of the provided Template parameters matters.
Since the plugins get initialised in the given order, `SDL_GUI::Core` should always come first.

## Core
The core of this library is itself a plugin [inc/plugins/core.h](inc/plugins/core.h). It encapsulates the rendering of a given render tree. All other functionality has to be provided by custom plugins.

## Custom Plugin
*There is an example custom plugin at [inc/plugins/example_plugin.h](inc/plugins/example_plugin.h).*

A custom plugin is a class derived from `SDL_GUI::PluginBase` with an init function:
```
template <typename ... Ts>
void init(SDL_GUI::ApplicationBase *app, std::tuple<Ts...> plugins)
```

This init function should create models and controllers (and maybe even views) and register them at the `SDL_GUI::Application`.
The `plugins` parameter holds the already initialised plugins, these are exactly those, that were mentioned before the current plugin in the template parameter list of the application.
Since `plugins` is an `std::tuple`, you can use `std::get<PluginType>(plugins)` to access the plugin of type `PluginType`.
The init function is the only point at which plugins know of each other.
If you want Plugins to communicate with each other, you should save the references here.

*It is not yet possible to know of plugins that come after the current one in the application's template parameter list.
This is planned to be changed with a `post_init` function that holds a tuple of all plugins.*

## Controllers
A controller is a class derived from `SDL_GUI::ControllerBase` with an overloaded `update()` function.
A controller has to be registered at the application using the `add_controller()` member function, so that the `update()` function can be called.
The application calls the `update()` function of all registered controllers once every iteration of the update loop.

Controllers should not have an internal state but use models that might be shared between multiple controllers.

## Models
A model is a class derived from `SDL_GUI::ModelBase`.
It represents a portion of the applications state data.
A model should only hold data and its member functions should define a low-level interface to access that data.
Models do not have to but can be registered at the application to ensure the destruction at the application's shut down.

## Controller and Model for Input
There is a specific model and a specific controller for handling input: `SDL_GUI::InputModel<InputValue, InputState>` and `SDL_GUI::Inputcontroller<InputValue, InputState>`.
Those two make sure that a configured set of input values can be accessed with `is_pressed()`, `is_down()`, and `is_up()` from the model.
The return value of these functions depends on the state, the input model is in.
The model also holds the current mouse position, the difference to the prior mouse position and the mouse wheel movement.

To configure the user input, the following has to be provided:
 - an `enum class InputState` with the set of possible input states (the name might vary)
 - an `enum class InputValue` with the set of possible input values (the name might vary)
 - a default input state (a value from `InputState`)
 - an input event value to quit the application (a value from `InputValue')
 - an `std::map<InputState, std::map<std::set<SDL_Scancode>, std::map<SDL_Scancode, InputValue>>> keyboard_input_config`
 - an `std::map<SDL_WindowEventID, InputValue> window_event_config`
 - an `std::map<InputState, std::map<std::set<SDL_Scancode>, std::map<Uint8, InputValue>>> mouse_input_config`

The InputController can be in different states that can lead to different actions being executed when the same input happens.
The state is the first layer of template encapsulation in this configurations.
The second layer is an `std::set` of `SDL_Scancode`s, the modifier keys.
Every key can be a modifier.
You have to provide an `std::set` to be able to combine them.
The last layer is the SDL input itself, that is an `SDL_Scancode` for the  `keyboard_event_config` and a `Uint8` for the `mouse_event_config`.

To use the user input, this library provides, instantiate the `SDL_GUI::InputModel<InputValue, InputState> input_model(default_input_state)` first, since the controller's constructor requires it.
Then instantiate the `SDL_GUI::InputController<InputValue, InputState>(input_model, keyboard_input_config, window_event_config, mouse_input_config, quit_input)`.
Finally, register the controller at the application.

## InterfaceModel
The `SDL_GUI::Core` plugin holds an `SDL_GUI::InterfaceModel` that you can access via the `interface_model()` member function.
This model comprises the render tree that consists of `SDL_GUI::Drawable` objects.
The interface model has member functions to search or manipulate the render tree.
See [inc/models/interface_model.h](inc/models/interface_model.h).

## Drawables
The abstract class `SDL_GUI::Drawable` describes an entity that can be rendered.
SDL_GUI provides a small number of specific drawable implementations in [inc/gui/primitives](inc/gui/primitives):

 - `SDL_GUI::Circle`
 - `SDL_GUI::Line`
 - `SDL_GUI::Polygon`
 - `SDL_GUI::Rect`
 - `SDL_GUI::Text`
 - `SDL_GUI::Texture`
 - `SDL_GUI::VerticalLine`
 - `SDL_GUI::WrapRect`
