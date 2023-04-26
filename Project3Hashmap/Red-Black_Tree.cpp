#pragma once
#include <iostream>
#include <vector>
#include "Director.h"
#include "Red-Black_Tree.h"
using namespace std;

//Map class

Map* Map::root = nullptr;
//Inserts new node into the map class, if the strings are the same then it adds the director to the vector
void Map::insert(string first, Director second) {
	Map* temp = iterator(first);
	if (temp == nullptr) {
		insertNew(first)->value.push_back(second);
	}
	else {
		temp->value.push_back(second);
	}
}
// helper method for insert
Map* Map::insertNew(string first)
{
	//numElm++;
	Map* newNode = createNode(first);
	if (root == nullptr) {
		root = newNode;
		return root;
	}
	Map* temp = root, * prev = nullptr;
	while (temp != nullptr) {
		prev = temp;
		if (first < temp->key) {
			temp = temp->left;
		}
		else if(first > temp->key){
			temp = temp->right;
		}
		else {
			return temp;
		}
	}
	if (first < prev->key) {
		prev->left = newNode;
	}
	else {
		prev->right = newNode;
	}
	newNode->parent = prev;
	balance(newNode);

	return newNode;
}
// creates new node
Map* Map::createNode(string first)
{
	
	Map* newNode = new Map;
	if (newNode) {
		newNode->key = first;
		newNode->value = {};
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = nullptr;
		newNode->color = 0;
	}
	return newNode;
}
//iterates through the map to find a node
Map* Map::iterator(string first)
{
	Map* temp = root;
	while (temp != nullptr && temp->key != first) {
		if (first < temp->key) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	return temp;
}
string Map::findClosestDirector(Director &similarDirector) {
    Map* genreNode = iterator(similarDirector.getGenreString());
    std::pair<int, double> mostSimilar;
    mostSimilar.first = -1;
    mostSimilar.second = 200000000;
    double foo;
    for (int i = 0; i < genreNode->value.size(); i++) {
        if (similarDirector.getDirectorName() == genreNode->value.at(i).getDirectorName()) {
            continue;
        }
        foo = similarDirector.calculateGenreDifference(genreNode->value.at(i));
        if (foo < mostSimilar.second) {
            mostSimilar.first = i;
            mostSimilar.second = foo;
        }
    }
    return genreNode->value.at(mostSimilar.first).getDirectorName();
}
// rotate left at node x
void Map::leftRotate(Map* x) {
	Map* y = x->right;
	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

// rotate right at node x
void Map::rightRotate(Map* x) {
	Map* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}
// red-black tree balance
void Map::balance(Map* k) {
	Map* u;
	while (k->parent->color == 1) {
		if (k->parent == k->parent->parent->right) {
			u = k->parent->parent->left; 
			if (u->color == 1) {
				
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->left) {
					
					k = k->parent;
					rightRotate(k);
				}
				
				k->parent->color = 0;
				k->parent->parent->color = 1;
				leftRotate(k->parent->parent);
			}
		}
		else {
			u = k->parent->parent->right; 

			if (u->color == 1) {
				
				u->color = 0;
				k->parent->color = 0;
				k->parent->parent->color = 1;
				k = k->parent->parent;
			}
			else {
				if (k == k->parent->right) {
					
					k = k->parent;
					leftRotate(k);
				}
				
				k->parent->color = 0;
				k->parent->parent->color = 1;
				rightRotate(k->parent->parent);
			}
		}
		if (k == root) {
			break;
		}
	}
	root->color = 0;
}
// Returns a node pointer
Map* Map::find(string first) {
	return iterator(first);
}
// prints the entire map in order
void Map::print(Map* head) {

	if (root == 0)
		return;
	if (head->left != 0) {
		print(head->left);
	}

	cout << head->key << ' ';
	for (int i = 0; i < head->value.size(); i++) {
		cout << head->value.at(i).getDirectorName() << ' ' << head->value.at(i).getNCosnt() << ' ';
	}
	cout << endl;
	if (head->right != 0) {
		print(head->right);
	}

}
//loops through the vector of a specific node and prints out the directors values
void Map::printValue(Map* x) {
	for (int i = 0; i < x->value.size(); i++) {
		cout << x->value.at(i).getDirectorName() << ' ' << x->value.at(i).getNCosnt();
	}
	cout << endl;
}


//int main() {
//	Map map;
//	directorClass director;
//	string name, other;
//	int num;
//	director.name = "tim";
//	director.num = 1;
//	map.insert("person8", director);
//	director.name = "tom";
//	director.num = 2;
//	map.insert("person2", director);
//	director.name = "tam";
//	director.num = 3;
//	map.insert("person3", director);
//	director.name = "ting";
//	director.num = 4;
//	map.insert("person4", director);
//	director.name = "tong";
//	director.num = 5;
//	map.insert("person1", director);
//	map.print();
//
//	cout << map.find("person1")->key << endl;
//	map.printValue(map.find("person1"));
//	return 0;
//}
