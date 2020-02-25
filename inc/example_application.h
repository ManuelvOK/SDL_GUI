#pragma once

#include <string>

#include "application.h"
#include "input_keys.h"
#include "models/keyboard_input_model.h"
#include "models/mouse_input_model.h"

namespace SDL_GUI {
class ExampleApplication : public Application {
    KeyboardInputModel<InputKey> *_keyboard_input_model = nullptr;

    /**
     * update this->is_running variable
     */
    void update_running() override;
public:
    /**
     * Constructor
     * @param application_title title string for the application
     */
    ExampleApplication(std::string application_title) : Application(application_title) {}

    /**
     * creates all the needed Models, Controllers and Views
     */
    void init_MVCs() override;
};
}
