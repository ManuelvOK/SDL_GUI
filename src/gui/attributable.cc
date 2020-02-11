#include <gui/attributable.h>

#include <algorithm>

using namespace SDL_GUI;

void Attributable::add_attribute(std::string attribute) {
    this->_attributes.push_back(attribute);
}

void Attributable::add_attributes(std::vector<std::string> attributes) {
    this->_attributes.insert(this->_attributes.end(), attributes.begin(), attributes.end());
}

bool Attributable::has_attribute(std::string attribute) {
    return (std::find(this->_attributes.begin(), this->_attributes.end(), attribute) != this->_attributes.end());
}
