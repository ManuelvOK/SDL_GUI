#pragma once

#include "rgb.h"

namespace SDL_GUI {
class Style {
public:
    RGB _color; /**< background color */
    RGB _border_color; /**< border color */
    bool _border = false; /**< border flag */
};
}
