#pragma once

#include "models/model_base.h"

class ControllerBase {
public:
    /**
     * default destructor
     */
    virtual ~ControllerBase() = default;

    /**
     * function that gets triggered every iteration in the applications main loop. Has to be overridden
     */
    virtual void update() = 0;

protected:
    /**
     * Constructor
     */
    ControllerBase() = default;
};
