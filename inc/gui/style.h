#pragma once

#include "rgb.h"

namespace SDL_GUI {
class Style {
public:
    RGB _color = RGB(255); /**< background color */
    RGB _border_color = RGB(0); /**< border color */
    bool _border = false; /**< border flag */

    Style() = default;
};
}
