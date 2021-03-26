#pragma once

#include "rect.h"

namespace SDL_GUI {

class WrapRect : public Rect {
    WrapRect(std::string type, Position position = {0,0})
        : Rect(type, position) {}

public:
    WrapRect(Position position = {0, 0})
        : WrapRect("WrapRect", position) {}
    virtual void update();
};

}
