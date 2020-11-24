#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

#include "../drawable.h"

namespace SDL_GUI {
/** primitive for rendering text */
class Text : public Drawable {
protected:
    SDL_Surface *_surface = nullptr;    /**< SDL surface to put text on */
    TTF_Font *_font;                    /**< Font to use */
    std::string _text;                  /**< text to display */

    /** apply the current style and render the text to the surface */
    void create_surface();

    void hook_set_current_style(Style *style) override;
public:
    /**
     * Constructor
     * @param font font to display the text in
     * @param text the text to display
     * @param position local position inside parent drawable
     */
    Text(TTF_Font *font, const std::string text = "", Position position = {0, 0});

    /** Destructor */
    ~Text();

    void draw(SDL_Renderer *renderer, Position position) const override;

    unsigned width() const override;

    unsigned height() const override;

    /**
     * change text to display
     * @param text text to display
     */
    void set_text(const std::string text = "");
};
}
