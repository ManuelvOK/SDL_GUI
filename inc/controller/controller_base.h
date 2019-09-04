#pragma once

#include <model/model_base.h>

class ControllerBase {
public:
    virtual ~ControllerBase() = default;

    virtual void update() = 0;

protected:
    ControllerBase() = default;
};
