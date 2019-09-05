#pragma once

#include <models/model_base.h>

class ViewBase {
public:
    /**
     * Destructor
     */
    virtual ~ViewBase() = default;

    void set_model(ModelBase *model) {
        this->_model = model;
    }

    bool has_model() const {
        return (this->_model != nullptr);
    }

    virtual bool init() = 0;
    virtual void deinit() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void frame_init() {};

protected:
    /**
     * Constructor
     */
    ViewBase() = default;

    ModelBase *_model = nullptr;
};
