#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <utility>
#include <vector>

struct Movie {
    std::string name;
    double rating{0.0};

    // operator overloading to compare movies alphabetically by name
    bool operator<(const Movie& other) const {
        return name < other.name;
    }
};

class MovieIndex {
public:
    void addMovie(const std::string& title, double rating);

    // sorts movies alphabetically
    void sortByTitle();

    // getter
    const std::vector<Movie>& getMovies() const { return movies_; }

    // finds range of movies that start with prefix
    std::pair<size_t, size_t> findPrefixRange(const std::string& prefix) const;

private:
    std::vector<Movie> movies_;
};

#endif