#include "movies.h"
#include <algorithm>

// add a movie to the list
void MovieIndex::addMovie(const std::string& title, double rating) {
    movies_.push_back(Movie{title, rating});
}

// sort movies alphabetically
void MovieIndex::sortByTitle() {
    std::sort(movies_.begin(), movies_.end());
}

// finds range of movies that start with prefix
std::pair<size_t, size_t> MovieIndex::findPrefixRange(const std::string& prefix) const {
    Movie low{prefix, 0.0};
    auto startIt = std::lower_bound(movies_.begin(), movies_.end(), low);

    std::string upper = prefix;
    upper.push_back(static_cast<char>(0x7F));

    Movie high{upper, 0.0};
    auto endIt = std::lower_bound(movies_.begin(), movies_.end(), high);

    return {
        static_cast<size_t>(startIt - movies_.begin()),
        static_cast<size_t>(endIt - movies_.begin())
    };
}