#pragma once

#include <SDL2/SDL_ttf.h>

#include <gui/drawable.h>
#include <util/tree_builder.h>

class DrawableTreeBuilder : public TreeBuilder<Drawable> {
    enum class Type {
        RECT,
        TEXT,
    };
    const std::map<std::string, Type> _type_map = {
        {"rect", Type::RECT},
        {"text", Type::TEXT}
    };
    TTF_Font *_font;
public:
    DrawableTreeBuilder(TTF_Font *font) : _font(font) {}
    Drawable *construct_node(std::string type, std::map<std::string, std::string> attributes) override;
    void add_child(Drawable *parent, Drawable *child) override;
};
