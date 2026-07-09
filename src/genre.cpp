#include "genre.h"

#include <string>

namespace library_system {

Genre::Genre(int genreId, std::string genre)
    : genreId(genreId), genre(genre) {}

// Get methods
int Genre::getGenreId() const { return genreId; }
std::string Genre::getGenre() const { return genre; }
}