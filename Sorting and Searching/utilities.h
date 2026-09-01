#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

// checks if a string starts with a prefix
inline bool starts_with(const std::string& text, const std::string& prefix) {
    return text.size() >= prefix.size() &&
           text.compare(0, prefix.size(), prefix) == 0;
}

#endif