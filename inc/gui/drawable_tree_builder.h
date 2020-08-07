#pragma once

#include <SDL2/SDL_ttf.h>

#include "drawable.h"
#include "../util/tree_builder.h"

namespace SDL_GUI {
class DrawableTreeBuilder : public TreeBuilder<Drawable> {
    enum class Type {
        RECT,
        TEXT,
        VERTICAL_LINE,
    };
    const std::map<std::string, Type> _type_map = {
        {"rect", Type::RECT},
        {"text", Type::TEXT},
        {"vertical-line", Type::VERTICAL_LINE},
    };

    enum class StyleType {
        BORDER,
        BACKGROUND,
        COLOR,
        WIDTH,
        HEIGHT,
        POSITION_X,
        POSITION_Y,
        OVERFLOW,
    };
    const std::map<std::string, StyleType> _style_type_map = {
        {"border", StyleType::BORDER},
        {"bg", StyleType::BACKGROUND},
        {"color", StyleType::COLOR},
        {"width", StyleType::WIDTH},
        {"height", StyleType::HEIGHT},
        {"x", StyleType::POSITION_X},
        {"y", StyleType::POSITION_Y},
        {"overflow", StyleType::OVERFLOW},
    };

    TTF_Font *_font;

    void set_style(Drawable *drawable, std::map<std::string, std::string> attributes) const;

    void set_color_of_drawable(Drawable *drawable, std::string color_value) const;
public:
    DrawableTreeBuilder(TTF_Font *font) : _font(font) {}
    Drawable *construct_node(std::string type, std::map<std::string, std::string> attributes) const override;
};
}
