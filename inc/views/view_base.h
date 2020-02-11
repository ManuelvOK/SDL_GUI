#pragma once

#include "../models/model_base.h"

class ViewBase {
public:
    /**
     * Destructor
     */
    virtual ~ViewBase() = default;

    /**
     * couple a model to this view
     * @param model pointer to the model to relate on
     */
    void set_model(ModelBase *model) {
        this->_model = model;
    }

    /**
     * check if this view has a model
     * @returns true if there is a model for this view. Otherwise false.
     */
    bool has_model() const {
        return (this->_model != nullptr);
    }

    /**
     * initialise view. Has to be overridden by implementation
     * @returns true if initialisation succeeded. Otherwise false.
     */
    virtual bool init() = 0;
    /**
     * deinitialise view. Has to be overridden by implementation
     */
    virtual void deinit() = 0;
    /**
     * update view. This gets called every iteration of the Applications main loop. Has to be overridden by implementaiton.
     */
    virtual void update() = 0;
    /**
     * render view. This gets called every iteration of the Applications main loop. Has to be overridden by implementation.
     */
    virtual void render() = 0;
    /**
     * TODO: what is this?
     */
    virtual void frame_init() {};

protected:
    /**
     * Constructor
     */
    ViewBase() = default;

    /**
     * pointe rto the coupled model.
     */
    ModelBase *_model = nullptr;
};
