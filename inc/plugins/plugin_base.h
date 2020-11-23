#pragma once

#include <string>
#include <vector>

namespace SDL_GUI {
/**
 * Base class for all the plugins.
 */
class PluginBase {
protected:

    /**
     * Plugin name
     */
    std::string _name = "";

    /**
     * Constructor
     * @param name Plugin name
     */
    PluginBase(std::string name) : _name(name) {}
};
}
