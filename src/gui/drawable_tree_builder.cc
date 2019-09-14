#include <gui/drawable_tree_builder.h>

#include <algorithm>
#include <cctype>

#include <gui/primitives/rect.h>
#include <gui/primitives/text.h>

//void DrawableTreeBuilder::add_child(Drawable *parent, Drawable *child) {
//    parent->add_child(child);
//}

Drawable *DrawableTreeBuilder::construct_node(std::string type, std::map<std::string, std::string> attributes) {
    (void) attributes;
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
    return drawable;
}
