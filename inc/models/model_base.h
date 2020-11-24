#pragma once

namespace SDL_GUI {
/** Base class for all the applications Models */
class ModelBase {
public:
    /** default destructor */
    virtual ~ModelBase() = default;
protected:
    /** default contructor */
    ModelBase() = default;
};
}
