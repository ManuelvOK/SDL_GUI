#pragma once

#include <map>
#include <string>

#include <SDL2/SDL.h>

/**
 * Color Code for RGB color
 */
namespace SDL_GUI {
class RGB {
public:
    unsigned char _r = 0; /**< red value between 0 and 255 */
    unsigned char _g = 0; /**< green value between 0 and 255 */
    unsigned char _b = 0; /**< blue value between 0 and 255 */
    unsigned char _a = 255; /**< apha value between 0 and 255 */

    std::map<std::string, std::array<unsigned char, 4>> _predefinitions = {
        {"red", {255, 0, 0, 255}},
    };

    /**
     * Default constructor
     */
    RGB() = default;

    /**
     * Constructor for grey color
     *
     * @param grey
     *   value for r, g and b
     */
    RGB(unsigned char grey) : _r(grey), _g(grey), _b(grey) {}

    /**
     * Constructor
     *
     * @param r
     *   red value between 0 and 255
     * @param g
     *   green value between 0 and 255
     * @param b
     *   blue value between 0 and 255
     */
    RGB(unsigned char r, unsigned char g, unsigned char b) : _r(r), _g(g), _b(b) {}

    RGB(std::string color);

    /**
     * conversion operator for SDL_Color
     */
    operator SDL_Color() const;

    /**
     * activate color for a given alpha on a given renderer
     *
     * @param renderer
     *   renderer to activate color on
     * @param alpha
     *   alpha value for the color to activate
     */
    void activate(SDL_Renderer *renderer) const;
};
}
