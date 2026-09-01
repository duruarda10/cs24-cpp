// Winter'26
// Instructor: Diba Mirza
// Student name: Duru Arda

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool getMovieInfo(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename prefixFilename" << endl;
        return 1;
    }

    // open movie file
    ifstream movieFile(argv[1]);
    if (movieFile.fail()) {
        cerr << "Could not open file " << argv[1] << endl;
        return 1;
    }

    MovieIndex index;

    // read movies from file
    string line, movieName;
    double movieRating;

    while (getline(movieFile, line) && getMovieInfo(line, movieName, movieRating)) {
        index.addMovie(movieName, movieRating);
    }

    movieFile.close();

    // sort movies alphabetically
    index.sortByTitle();

    // print all movies if no prefix file provided
    if (argc == 2) {
        for (const Movie& m : index.getMovies()) {
            cout << m.name << ", "
                 << fixed << setprecision(1) << m.rating << endl;
        }
        return 0;
    }

    // open prefix file
    ifstream prefixFile(argv[2]);
    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2] << endl;
        return 1;
    }

    vector<string> prefixes;

    // read prefixes
    while (getline(prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    prefixFile.close();

    // store best movie for each prefix
    struct BestMovie {
        string prefix;
        bool found{false};
        string name;
        double rating{0.0};
    };

    vector<BestMovie> bestList;
    bestList.reserve(prefixes.size());

    // process each prefix in order
    for (const string& prefix : prefixes) {

        auto range = index.findPrefixRange(prefix);
        size_t start = range.first;
        size_t end   = range.second;

        // no matches
        if (start == end) {
            cout << "No movies found with prefix " << prefix << endl;
            bestList.push_back(BestMovie{prefix, false, "", 0.0});
            continue;
        }

        // collect matching movies
        vector<const Movie*> matches;
        matches.reserve(end - start);

        const auto& movies = index.getMovies();

        for (size_t i = start; i < end; i++) {
            matches.push_back(&movies[i]);
        }

        // sort matches by rating descending, then name ascending
        sort(matches.begin(), matches.end(),
            [](const Movie* a, const Movie* b) {
                if (a->rating != b->rating) return a->rating > b->rating;
                return a->name < b->name;
            }
        );

        // Part 2a: print matches
        for (const Movie* m : matches) {
            cout << m->name << ", "
                 << fixed << setprecision(1) << m->rating << endl;
        }

        cout << endl;

        // save best movie for Part 2b
        bestList.push_back(BestMovie{
            prefix, true, matches[0]->name, matches[0]->rating
        });
    }

    // Part 2b: print best movies at the end
    for (const BestMovie& b : bestList) {
        if (!b.found) continue;

        cout << "Best movie with prefix " << b.prefix << " is: "
             << b.name << " with rating "
             << fixed << setprecision(1) << b.rating << endl;
    }

    return 0;
}

/*
Measured Running Times
./runMovies input_20_random.csv   prefix_large.txt  : 535 ms
./runMovies input_100_random.csv  prefix_large.txt  : 507 ms
./runMovies input_1000_random.csv prefix_large.txt  : 487 ms
./runMovies input_76920_random.csv prefix_large.txt : 2544 ms
When the number of inputs is small (for example, between 20-1000), the running time is around 500 ms. 
However, when the number of inputs increases to 76920, the running time increases significantly to 2544 ms. 
This suggests that the algorithm's performance degrades as the input size grows due to the increased number of comparisons and sorting operations required for larger datasets.

Part 3a: Time Complexity
We assume that:
- n movies are stored in a vector and sorted alphabetically by title.
- m prefixes are stored in an array.
- at most k movies match a prefix.
- l is the max length of a movie title (or prefix).

For each prefix:
1) findPrefixRange(prefix):
   - uses two std::lower_bound calls on the sorted vector
   - each lower_bound takes O(log n) comparisons
   - each string comparison can cost up to O(l) in the worst case
   => O(l log n)

2) collect the k matching movies into a list of pointers:
   => O(k)

3) sort the k matches by (rating desc, name asc):
   - std::sort on k items is O(k log k) comparisons
   - comparisons are usually O(1) for rating, but ties compare names (up to O(l))
   => worst-case O(l k log k)

So per prefix: O(l log n + k + l k log k)
Worst-case total over all prefixes:
  O(m * (l log n + k + l k log k))
Often written as:
  O(m * (l log n + l k log k))

Part 3b: Space Complexity
Extra space (not counting the input movies/prefixes themselves):
- For each prefix, we store up to k pointers in a temporary vector:
  => O(k)
- Best-movie results store 1 item per prefix:
  => O(m)

Worst-case extra space:
  O(k + m)

Part 3c: Time/Space Tradeoffs (Reflection)
I mainly optimized for time while keeping the code/data structures simple.
Sorting the movies once lets me use binary search (lower_bound) to find the
matching title range for each prefix, instead of scanning all n movies each time.
That keeps each prefix lookup fast.

To rank matches by rating, I still sort the k matching movies, which adds
O(k log k) work per prefix. This uses a small amount of extra memory (O(k))
for a temporary list of matches.

A faster approach for repeated prefix queries could use a trie or a more complex
index, but that would take more memory and be harder to implement/debug.
My solution is a reasonable balance: good speed, and not too much extra space.

*/

bool getMovieInfo(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex + 1));

    // remove quotes if they are present
    if (!movieName.empty() && movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }

    return true;
}