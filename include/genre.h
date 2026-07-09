#pragma once

#include <string>

namespace library_system{

class Genre {
    public:
        Genre(int, std::string);

        // Get methods
        int getGenreId() const;
        std::string getGenre() const;

    private:
        int genreId;
        std::string genre;
};

}