#include <controllers/input_controller.h>

using namespace SDL_GUI;

static std::vector<SDL_Event> _events;

void SDL_GUI::read_sdl_events() {
    SDL_Event event;
    while (0 != SDL_PollEvent(&event)) {
        _events.push_back(event);
    }
}

void SDL_GUI::clear_sdl_events() {
    _events.clear();
}

const std::vector<SDL_Event> SDL_GUI::events() {
    return _events;
}
