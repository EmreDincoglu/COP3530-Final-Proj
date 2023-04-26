#pragma once
using namespace std;
class Map {
    static class Map* root;
public:
    int numElm = 0;
    string key;
    int color;
    vector<Director> value;
    Map* left, * right, * parent;

    void insert(string first, Director second);
    Map* insertNew(string first);
    Map* createNode(string first);
    Map* iterator(string first);
    void leftRotate(Map* x);
    void rightRotate(Map* x);
    void balance(Map* k);
    Map* find(string first);
    void print(Map* head = root);
    void printValue(Map* x);
    std::string findClosestDirector(Director &similarDirector);
};