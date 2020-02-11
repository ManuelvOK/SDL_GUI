#pragma once

#include "controllers/controller_base.h"

class InterfaceController : public ControllerBase {
public:
    void update() override;
};
