#pragma once

#include <map>
#include <string>

template <typename T>
class TreeBuilder {
public:
    virtual T *construct_node(std::string type, std::map<std::string, std::string> attributes) = 0;
    virtual void add_child(T *parent, T *child) = 0;
};
