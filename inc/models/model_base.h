#pragma once

namespace SDL_GUI {
class ModelBase {
public:
    /**
     * default destructor
     */
    virtual ~ModelBase() = default;
protected:
    /**
     * default contructor
     */
    ModelBase() = default;
};
}
