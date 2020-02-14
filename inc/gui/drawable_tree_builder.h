#pragma once

#include <SDL2/SDL_ttf.h>

#include "drawable.h"
#include "../util/tree_builder.h"

namespace SDL_GUI {
class DrawableTreeBuilder : public TreeBuilder<Drawable> {
    enum class Type {
        RECT,
        TEXT,
    };
    const std::map<std::string, Type> _type_map = {
        {"rect", Type::RECT},
        {"text", Type::TEXT},
    };

    enum class StyleType {
        BORDER,
        BACKGROUND,
        WIDTH,
        HEIGHT,
        POSITION_X,
        POSITION_Y,
    };
    const std::map<std::string, StyleType> _style_type_map = {
        {"border", StyleType::BORDER},
        {"bg", StyleType::BACKGROUND},
        {"width", StyleType::WIDTH},
        {"height", StyleType::HEIGHT},
        {"x", StyleType::POSITION_X},
        {"y", StyleType::POSITION_Y},
    };

    TTF_Font *_font;

    void set_style(Drawable *drawable, std::map<std::string, std::string> attributes) const;
public:
    DrawableTreeBuilder(TTF_Font *font) : _font(font) {}
    Drawable *construct_node(std::string type, std::map<std::string, std::string> attributes) const override;
    //void add_child(Drawable *parent, Drawable *child) override;
};
}
