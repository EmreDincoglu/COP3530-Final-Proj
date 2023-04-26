#pragma once
#include "Director.h"
class HashNode {
private:
    std::string genreString;
    std::vector<Director> directorList;
public:

    HashNode();

    HashNode(std::string genreString);

    void addDirector (Director newDirector);

    void changeGenreString(std::string newGenreString);

    std::string getGenreString();

    std::string findSimilarDirector(Director &similarDirector);
};



