#pragma once
#include <algorithm>
#include "Director.h"

Director::Director() {
directorName = "";
nConst = "";
GenreString = "";
numOfMovies = 0;
}

Director::Director(std::string directorsName) {
    directorName = directorsName;
    GenreString = "";
    numOfMovies = 0;
}

std::string Director::calculateGenreString() {
    std::sort(genreCount.begin(), genreCount.end());
    int genreStringLength = 5;
    if (genreCount.size() < 5) {
        genreStringLength = genreCount.size();
    }
    std::vector<std::string> genreStringSort;
    genreStringLength = genreCount.size() - genreStringLength;
    for (int i = genreCount.size() - 1; i >= genreStringLength; i--) {
        genreStringSort.push_back(genreCount.at(i).second);
    }
    std::sort(genreStringSort.begin(), genreStringSort.end());
    std::string finalGenreString;
    finalGenreString += genreStringSort.at(0);
    std::pair<double, std::string> percentPair1;
    percentPair1.second = genreStringSort.at(0);
    percentages.push_back(percentPair1);
    for (int i = 1; i < genreStringSort.size(); i++) {
        finalGenreString += ",";
        finalGenreString += genreStringSort.at(i);
        std::pair<double, std::string> percentPair2ToN;
        percentPair2ToN.second = genreStringSort.at(i);
        percentages.push_back(percentPair2ToN);
    }
    GenreString = finalGenreString;
    calculatePercentages();
    return GenreString;
}

void Director::addGenreNum(unsigned int numOfGenre, const std::string& genre) {
    bool hitGenre = false;
    int genreSize;
    for (int i = 0; i < genreCount.size(); i++) {
        if (genreCount.at(i).second == genre) {
            genreCount.at(i).first += numOfGenre;
            hitGenre = true;
            break;
        }
    }
    if (!hitGenre) {
        std::pair<unsigned int, std::string> newGenrePair;
        newGenrePair.second = genre;
        newGenrePair.first = numOfGenre;
        genreCount.push_back(newGenrePair);
    }
}

void Director::addDirectedGenre(std::string genres)
{
    std::string temp = genres;
    int x = 0;
    while (genres.find('|') != std::string::npos)
    {
        temp = genres.substr(0, genres.find('|'));
        if (temp.size() >= 2) {
            addGenreNum(1, temp);
        }
        genres = genres.substr(genres.find('|') + 1, genres.size() - 1);

        x = genres.find('|') + 1;
    }
    if (genres.size() >= 2)
    {
        addGenreNum(1,genres);
    }
}

std::string Director::getGenreString() {
    return GenreString;
}

void Director::calculatePercentages() {
    double num1;
    double num2;
    num2 = numOfMovies;
    for (int i = 0; i < percentages.size(); i++) {
        for (int j = genreCount.size() - 1; j >= 0; j--) {
            if (percentages.at(i).second == genreCount.at(j).second) {
                num1 = genreCount.at(j).first;
                percentages.at(i).first = num1/num2;
            }
        }
    }
}

std::string Director::getDirectorName() {
    return directorName;
}

double Director::calculateGenreDifference(Director &otherDirector) {
    double totalValue = 0;
    std::vector<std::pair<double, std::string>> otherDirectorPercentages = otherDirector.getPercentageVector();
    for (int i = 0; i < otherDirectorPercentages.size(); i++) {
        totalValue += this->percentages.at(i).first - otherDirectorPercentages.at(i).first;
        if (totalValue < 0) {
            totalValue *= -1;
        }
    }
    return totalValue;
}

std::vector<std::pair<double,std::string>> Director::getPercentageVector() {
    return percentages;
}

std::string Director::getNCosnt() {
    return nConst;
}

void Director::changeNConst(std::string &newNconst) {
    nConst = newNconst;
}

void Director::setNumOfMovies(std::string numOfMovies) {
    this->numOfMovies = std::stoi(numOfMovies);
}