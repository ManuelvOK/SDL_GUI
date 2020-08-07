#pragma once

#include <string>
#include <vector>

/**
 * An Object that holds one or more attributes to be identified
 */
namespace SDL_GUI {
class Attributable {
protected:
    std::vector<std::string> _attributes; /**< List of attributes */

public:
    /**
     * add an attribute to the object
     * @param attribute
     *   attribute to add
     */
    void add_attribute(std::string attribute);

    /**
     * add multiple attributes to the object
     *
     * @param attributes
     *   List of attributes
     */
    void add_attributes(std::vector<std::string> attributes);

    /**
     * check if the Object holds a given attribute
     *
     * @param attribute
     *   attribute to check for
     * @returns
     *   True if attribute is in the list of given attributes for this object. False otherwise.
     */
    bool has_attribute(std::string attribute) const;

    std::vector<std::string> attributes() const;
};
}
