#pragma once

#include "controller_base.h"

namespace SDL_GUI {
class InterfaceController : public ControllerBase {
public:
    void update() override;
};
}
