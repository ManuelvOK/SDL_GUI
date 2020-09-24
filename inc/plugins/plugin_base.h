#pragma once

#include <string>
#include <vector>

namespace SDL_GUI {
class PluginBase {
protected:

    /**
     * Plugin name
     */
    std::string _name = "";

    /**
     * Constructor
     * @param name Plugin name
     * @param application reference to Application object
     */
    PluginBase(std::string name) : _name(name) {}
};
}
