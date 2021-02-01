#include <util/command_line.h>

#include <iostream>

#include <limits>

using namespace SDL_GUI;

static std::vector<std::string> split_string(std::string s, std::string delimiter,
                                             unsigned max = -1);

bool CommandLine::parse_option(std::string argument) {
    /* options start with - */
    if (argument[0] != '-') {
        return false;
    }

    /* check if given key is a shortcut */
    argument = argument.substr(1);
    bool is_shortcut = (argument[0] != '-');
    if (not is_shortcut) {
        argument = argument.substr(1);
    }

    std::vector<std::string> split = split_string(argument, "=", 1);
    /* if there is no '=' its a flag */
    if (split.size() != 2) {
        return false;
    }
    std::string key = split[0];
    std::string value = split[1];

    /* find registered option */
    for (CommandLineOption &option: this->_options) {
        if ((is_shortcut && option._shortcut == key)
            || (not is_shortcut && option._key == key)) {
            this->_parsed_options.emplace(option._name, value);
            return true;
        }
    }
    return false;
}

bool CommandLine::parse_flag(std::string argument) {
    /* flags start with - */
    if (argument[0] != '-') {
        return false;
    }

    /* check if given argument is a shortcut */
    argument = argument.substr(1);
    bool is_shortcut = (argument[0] != '-');
    if (not is_shortcut) {
        argument = argument.substr(1);
    }

    /* find registered flag */
    for (CommandLineFlag &flag: this->_flags) {
        if ((is_shortcut && flag._shortcut == argument)
            || (not is_shortcut && flag._key == argument)) {
            this->_parsed_flags.emplace(flag._name, true);
            return true;
        }
    }
    return false;
}

bool CommandLine::parse_positional(unsigned position, std::string argument) {
    if (position >= this->_positionals.size()) {
        return false;
    }
    std::string key = this->_positionals[position];
    this->_parsed_positionals.emplace(key, argument);
    return true;
}

std::vector<std::string> split_string(std::string s, std::string delimiter, unsigned max){
    std::vector<std::string> ret;
    std::string part;
    unsigned pos;
    while (max != 0 and (pos = s.find(delimiter) != std::string::npos)) {
        ret.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
        --max;
    }
    ret.push_back(s);
    return ret;
}

void CommandLine::register_option(std::string key, std::string shortcut, std::string name) {
    if (name.empty()) {
        name = key;
    }
    this->_options.emplace_back(CommandLineOption{name, key, shortcut});
}

void CommandLine::register_flag(std::string key, std::string shortcut, std::string name) {
    if (name.empty()) {
        name = key;
    }
    this->_flags.emplace_back(CommandLineFlag{name, key, shortcut});
}

void CommandLine::register_positional(std::string name) {
    this->_positionals.push_back(name);
}

void CommandLine::parse(int argc, char *argv[]) {
    unsigned positional_pos = 0;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (this->parse_option(arg)) {
            continue;
        }

        if (this->parse_flag(arg)) {
            continue;
        }

        if (this->parse_positional(positional_pos, arg)) {
            positional_pos++;
        }
    }
}

std::string CommandLine::get_option(std::string key) const {
    if (this->_parsed_options.contains(key)) {
        return this->_parsed_options.at(key);
    }
    return "";
}

bool CommandLine::get_flag(std::string key) const {
    if (this->_parsed_flags.contains(key)) {
        return this->_parsed_flags.at(key);
    }
    return false;
}

std::string CommandLine::get_positional(std::string key) const {
    if (this->_parsed_positionals.contains(key)) {
        return this->_parsed_positionals.at(key);
    }
    return "";
}
