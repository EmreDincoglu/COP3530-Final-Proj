#pragma once
#include "HashNode.h"
HashNode::HashNode() {
    genreString = "";
}

HashNode::HashNode(std::string genreString){
    this->genreString = genreString;
}

void HashNode::addDirector (Director newDirector) {
    this->directorList.push_back(newDirector);
}

void HashNode::changeGenreString(std::string newGenreString) {
    this->genreString = newGenreString;
}

std::string HashNode::getGenreString() {
    return genreString;
}

std::string HashNode::findSimilarDirector(Director &similarDirector) {
    std::pair<int, double> mostSimilar;
    mostSimilar.first = -1;
    mostSimilar.second = 200000000;
    double foo;
    for (int i = 0; i < directorList.size(); i++) {
        if (similarDirector.getDirectorName() == directorList.at(i).getDirectorName()) {
            continue;
        }
        foo = similarDirector.calculateGenreDifference(directorList.at(i));
        if (foo < mostSimilar.second) {
            mostSimilar.first = i;
            mostSimilar.second = foo;
        }
    }
    return directorList.at(mostSimilar.first).getDirectorName();
}