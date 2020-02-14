#pragma once

#include <string>

#include "controller_base.h"
#include "../models/mouse_input_model.h"
#include "../models/interface_model.h"

namespace SDL_GUI {
class InterfaceController : public ControllerBase {
protected:
    /**
     * path to template file
     */
    const std::string _template_file_path;

    /**
     * pointer to the interface model
     */
    InterfaceModel *_interface_model;

    /**
     * pointer to the mouse intput model
     */
    const MouseInputModel *_mouse_input_model;

public:
    /**
     * Constructor
     * @param template_file_path path to the template file
     */
    InterfaceController(const std::string template_file_path,
            InterfaceModel *interface_model, const MouseInputModel *mouse_input_model);

    /**
     * init controller
     */
    virtual void init();

    virtual void update() override;
};
}
