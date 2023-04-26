#pragma once
#include <vector>
#include "Director.h"
#include "HashNode.h"
class hashMap {
private:
    unsigned int arraySize = 1000;
    unsigned int currentLoad = 0;
    const double loadFactor = .75;
    HashNode* hashArray = new HashNode[arraySize];

    unsigned int calculateHash(std::string key);
public:

    void insertNewDirector(Director insertingDirector);

    void doubleAndRehash();

    void rehashANode(HashNode rehasingNode, HashNode* newArray);

    std::string findClosestDirector(Director &similarDirector);
};



