#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <rapidxml/rapidxml.hpp>

#include "../gui/drawable.h"
#include "tree.h"
#include "tree_builder.h"


namespace SDL_GUI {
template <typename T>
class XmlParser {
    TreeBuilder<T> *_builder = nullptr;

    std::map<std::string, std::string> parse_attributes(rapidxml::xml_node<> *node) const {
        std::map<std::string, std::string> attributes;
        for (rapidxml::xml_attribute<> *attribute = node->first_attribute(); attribute != nullptr; attribute = attribute->next_attribute()) {
            attributes.insert({attribute->name(), attribute->value()});
        }
        return attributes;
    }

    TreeNode<T> *parse_node(rapidxml::xml_node<> *node) const {
        T *parsed_object = this->_builder->construct_node(node->name(), this->parse_attributes(node));
        TreeNode<T> *parsed_node = new TreeNode(parsed_object);
        for (rapidxml::xml_node<> *child = node->first_node(); child != nullptr; child = child->next_sibling()) {
            parsed_node->add_child(this->parse_node(child));
        }
        return parsed_node;
    }
public:
    XmlParser(TreeBuilder<T> *builder) : _builder(builder) {}

    Tree<T> *parse_file(std::string path) const {
        std::ifstream file(path);
        std::vector<char> buffer{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
        buffer.push_back('\0');
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);
        Tree<T> *tree = new Tree<T>();
        tree->set_root(this->parse_node(doc.first_node()));
        return tree;
    }

};
}
