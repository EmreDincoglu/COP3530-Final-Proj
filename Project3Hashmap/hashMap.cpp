#pragma once
#include "hashMap.h"

void hashMap::doubleAndRehash() {
    arraySize *= 2;
    HashNode* newHashArray = new HashNode[arraySize];
    for (int i = 0; i < arraySize / 2; i++) {
        rehashANode(hashArray[i], newHashArray);
    }
    delete[] hashArray;
    hashArray = newHashArray;
}

void hashMap::rehashANode(HashNode rehasingNode, HashNode* newArray) {
    if (rehasingNode.getGenreString() == "") {
        return;
    }
    unsigned int newHash;
    newHash = calculateHash(rehasingNode.getGenreString());
    newArray[newHash] = rehasingNode;
}

void hashMap::insertNewDirector(Director insertingDirector) {
    std::string genreString = insertingDirector.getGenreString();
    unsigned int hash;
    hash = calculateHash(genreString);
    unsigned int hashIncreaser = 1;
    do {
        if (hashArray[hash].getGenreString() == "") {
            HashNode newNode(genreString);
            newNode.addDirector(insertingDirector);
            hashArray[hash] = newNode;
            currentLoad++;
            if (currentLoad >= arraySize * loadFactor) {
                doubleAndRehash();
            }
            return;
        }
        if (hashArray[hash].getGenreString() == genreString) {
            hashArray[hash].addDirector(insertingDirector);
            return;
        }
        hash += hashIncreaser;
        hashIncreaser += 1;
        hashIncreaser %= arraySize;
    } while (1 == 1);
}

unsigned int hashMap::calculateHash(std::string key) {
    unsigned int hashedNumber = 0;
    unsigned int multiplier = 1;
    for (int i = 0; i < key.size(); i++) {
        hashedNumber += int (key.at(i)) * multiplier;
        multiplier++;
    }
    hashedNumber %= arraySize;
    return hashedNumber;
}

std::string hashMap::findClosestDirector(Director &similarDirector) {
    std::string genreString = similarDirector.getGenreString();
    unsigned int hash;
    hash = calculateHash(genreString);
    unsigned int hashIncreaser = 1;
    do {
        if (hashArray[hash].getGenreString() == genreString) {
            return hashArray[hash].findSimilarDirector(similarDirector);
        }
        hash += hashIncreaser;
        hashIncreaser += 1;
        hashIncreaser %= arraySize;
    } while (1 == 1);
}