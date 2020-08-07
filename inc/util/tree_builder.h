#pragma once

#include <functional>
#include <map>
#include <string>

namespace SDL_GUI {
template <typename T>
class TreeBuilder {
public:
    virtual T *construct_node(std::string type, std::map<std::string, std::string> attributes) const = 0;
};
}
