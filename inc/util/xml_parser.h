#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <rapidxml/rapidxml.hpp>

#include <gui/drawable.h>
#include <util/tree.h>
#include <util/tree_builder.h>


template <typename T>
class XmlParser {
    TreeBuilder<T> *_builder = nullptr;

    TreeNode<T> *parse_node(rapidxml::xml_node<> *node) const {
        T *parsed_object = this->_builder->construct_node(node->name(), {});
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

