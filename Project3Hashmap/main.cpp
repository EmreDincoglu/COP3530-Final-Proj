#include <iostream>
#include "hashMap.h"
#include "Director.h"
#include "Red-Black_Tree.h"
#include <fstream>
#include <string>
#include <sstream>
#include <map>

int main()
{
    std::cout << "Hello, and welcome to the IMDB Director finder where if you tell us your favorite director, \n"
                 "then we will find you a new Director who makes a similar make up of movies, please wait as we parse\n"
                 "through our extensive database!\n\n";

    // Map that allows you to seach of a director's acutal name given their nconst (IMDB Identifier)
    // [nconst, name]
    std::map<string, string> NameDict;

    //used so the user can type in a directors name into the console instead of their Nconst
    std::map<string, string> nameToNconst;

    // Main map that holds the nconst of a director as a key and the value being that director's Director class
    std::map<string, Director> DirectorMap;

    Map redBlackTree;
    hashMap DirectorHashMap;

    // opens the tsv file held in the same directory as main.cpp
    std::ifstream file("finalData.tsv");
    std::string line;

    if (!file.is_open())
    {
        cout << "Failed to Open File!!!" << endl;
    }

    getline(file, line);
    getline(file, line);
    //cout << line << endl << endl;
    std::stringstream ss(line);
    std::string item;

    std::string dirNum;
    std::string dirName;
    std::string genres;
    std::string numOfMovies;

    while (getline(file, line))
    {
        ss.clear();
        ss.str(line);


        getline(ss, dirNum, '\t');
        getline(ss, dirName, '\t');
        getline(ss, numOfMovies, '\t');
        getline(ss, genres, '\t');



        //cout << dirNum << endl << dirName << endl << numOfMovies << endl << genres << endl << endl;

        NameDict[dirNum] = dirName;
        Director director(dirName);
        director.changeNConst(dirNum);
        director.setNumOfMovies(numOfMovies);
        director.addDirectedGenre(genres);

        director.calculateGenreString();

        DirectorMap[dirNum] = director;
        nameToNconst.emplace(dirName, dirNum);

        redBlackTree.insert(director.getGenreString(),director);
        DirectorHashMap.insertNewDirector(director);
    }
    std::string directorChosen;
    std::cout << "Thank you for waiting, please go to IMDB, and copy and paste the director you wish to find similar too: ";
    getline(cin, directorChosen);
    std::cout << std::endl;

    directorChosen = nameToNconst.at(directorChosen);

    std::cout << "The hashMap thinks the closest director is: " << DirectorHashMap.findClosestDirector(DirectorMap.at(directorChosen)) << "\n";
    std::cout << "The red black tree thinks the closest director is: " << redBlackTree.findClosestDirector(DirectorMap.at(directorChosen));



    return 0;
}

