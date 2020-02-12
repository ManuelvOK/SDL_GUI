#include <gui/drawable_tree_builder.h>

#include <algorithm>
#include <cctype>
#include <sstream>

#include <gui/primitives/rect.h>
#include <gui/primitives/text.h>

using namespace SDL_GUI;

//void DrawableTreeBuilder::add_child(Drawable *parent, Drawable *child) {
//    parent->add_child(child);
//}
//
void DrawableTreeBuilder::set_style(Drawable *drawable, std::map<std::string, std::string> attributes) const {
    for (std::pair<std::string, std::string> attribute: attributes) {
        std::string key = attribute.first;
        std::string value = attribute.second;
        if (this->_style_type_map.find(key) == this->_style_type_map.end()) {
            continue;
        }
        switch (this->_style_type_map.at(key)) {
            case StyleType::BORDER:
                drawable->_default_style._border = true;
                drawable->_hover_style._border = true;
                break;
            case StyleType::BACKGROUND:
                drawable->_default_style._color = RGB(value);
                drawable->_hover_style._color = RGB(value);
                break;
            case StyleType::WIDTH:
                drawable->set_width(std::stoi(value));
                break;
            case StyleType::HEIGHT:
                drawable->set_height(std::stoi(value));
                break;
            case StyleType::POSITION_X:
                drawable->set_x(std::stoi(value));
                break;
            case StyleType::POSITION_Y:
                drawable->set_y(std::stoi(value));
                break;
            default:
                break;
        }
    }
}

Drawable *DrawableTreeBuilder::construct_node(std::string type, std::map<std::string, std::string> attributes) const {
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    Drawable *drawable;
    /* TODO: use attributes */
    switch(this->_type_map.at(type)) {
        case Type::RECT:
            drawable = new Rect();
            break;
        case Type::TEXT:
            drawable = new Text("test text", this->_font);
            break;
    }
    if (attributes.find("attributes") != attributes.end()) {
        std::stringstream ss(attributes["attributes"]);
        std::string attribute;
        while (ss >> attribute) {
            drawable->add_attribute(attribute);
        }
    }
    this->set_style(drawable, attributes);
    return drawable;
}
