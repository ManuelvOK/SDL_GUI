#pragma once

#include "gui/rgb.h"

class Style {
public:
    RGB _color; /**< background color */
    RGB _border_color; /**< border color */
    bool _border = false; /**< border flag */
};
