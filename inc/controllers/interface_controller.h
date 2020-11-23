#pragma once

#include <string>

#include "controller_base.h"
#include "../models/input_model.h"
#include "../models/interface_model.h"

namespace SDL_GUI {
/**
 * Controller for the Interface model.
 * This controller does change the style of a Drawable based on its hovering state.
 */
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
     * pointer to the input model
     */
    const InputModelBase *_input_model;

public:
    /**
     * Constructor
     * @param template_file_path path to the template file
     */
    InterfaceController(const std::string template_file_path, InterfaceModel *interface_model,
                        const InputModelBase *input_model);

    /**
     * init controller
     */
    virtual void init();

    /**
     * change style of hovered drawable
     */
    virtual void update() override;
};
}
