#pragma once

#include "rgb.h"

namespace SDL_GUI {
class Style {
public:
    RGB _color = RGB("white"); /**< background color */
    RGB _border_color = RGB("black"); /**< border color */
    bool _border = false; /**< border flag */

    Style() = default;
};
}
