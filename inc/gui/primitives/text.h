#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

#include "../drawable.h"

/**
 * A Text view
 */
namespace SDL_GUI {
class Text : public Drawable {
private:
    SDL_Surface *_surface = nullptr; /**< SDL surface to put text on */
    std::string _text; /**< text to display */
    TTF_Font *_font; /**< Font to use */

    /**
     * apply the current style and render the text to the surface
     */
    void create_surface();

    void hook_set_current_style(Style *style) override;
public:
    /**
     * Constructor
     *
     * @param text
     *   the text to display
     */
    Text(const std::string text, TTF_Font *font) : _text(text), _font(font) {}

    /**
     * Destructor
     */
    ~Text();

    void draw(SDL_Renderer *renderer, Position position) const override;

    unsigned width() const;

    unsigned height() const;
};
}
