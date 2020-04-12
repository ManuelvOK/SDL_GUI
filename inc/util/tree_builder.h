#pragma once

#include <map>
#include <string>

#include "tree.h"

namespace SDL_GUI {
template <typename T>
class TreeBuilder {
protected:
    std::function<void(T *)> _init_node_callback = nullptr;
public:
    virtual T *construct_node(std::string type, std::map<std::string, std::string> attributes) const = 0;
    virtual Tree<T> *construct_empty_tree() const = 0;
    virtual std::function<void(T *)> get_init_node_callback() {
        return this->_init_node_callback;
    }
};
}
