#pragma once
#include <vector>
#include <string>

class Director {
private:
    std::string directorName;
    std::string nConst;
    std::string GenreString;
    std::vector<std::pair<unsigned int, std::string>> genreCount;
    std::vector<std::pair<double, std::string>> percentages;
    unsigned int numOfMovies;

public:
    Director();

    Director(std::string directorsName);

    std::string calculateGenreString();

    void addGenreNum(unsigned int numOfGenre, const std::string& genre);

    void calculatePercentages();

    std::string getGenreString();

    std::string getDirectorName();

    double calculateGenreDifference(Director &otherDirector);

    std::vector<std::pair<double,std::string>> getPercentageVector();

    std::string getNCosnt();

    void changeNConst(std::string &newNconst);

    void setNumOfMovies(std::string numOfMovies);

    void addDirectedGenre(std::string genres);
};



