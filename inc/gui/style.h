#pragma once

#include "rgb.h"

namespace SDL_GUI {
class Style {
public:
    RGB _color = RGB(); /**< background color */
    RGB _border_color = RGB("black"); /**< border color */
    bool _has_background = false; /**< background flag */
    bool _has_border = false; /**< border flag */
    bool _overflow = false; /**< overflow flag */

    Style() = default;
};
}
