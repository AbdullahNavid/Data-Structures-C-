#ifndef QUADTREE_H
#define QUADTREE_H

/*****************************************
 * UW User ID:  anavid
 *  * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();


		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();

	
};
//Constructor initializes all the variabels ot be used in the program
template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	// empty constructor
}

//Destructor clears the root and sets size(count) of the tree to zero
template <typename T>
Quadtree<T>::~Quadtree() {
	if (root() != 0){
		root()->clear();
	}
	tree_root = 0;
	count = 0;
}

//Returns the size of the tree
template <typename T>
int Quadtree<T>::size() const {
	return count;
}

//check if the tree is empty by checking the size
template <typename T>
bool Quadtree<T>::empty() const {
	if (count == 0)
		return true;
	else
		return false;
}

//find the minimum x-value of the root and all its children by recursively going through the whole tree using the min_x method done in Quadtree_node.h
template <typename T>
T Quadtree<T>::min_x() const {
	if (empty()) throw underflow();
	return root()->min_x();
}

//find the minimum y-value of the root and all its children by recursively going through the whole tree using the min_y method done in Quadtree_node.h
template <typename T>
T Quadtree<T>::min_y() const {
	if (empty()) throw underflow();
	return root()->min_y();
}

//find the maximum x-value of the root and all its children by recursively going through the whole tree using the max_x method done in Quadtree_node.h
template <typename T>
T Quadtree<T>::max_x() const {
	if (empty()) throw underflow() ; 
	return root()->max_x();
}

//find the maximum y-value of the root and all its children by recursively going through the whole tree using the max_y method done in Quadtree_node.h
template <typename T>
T Quadtree<T>::max_y() const {
	if (empty()) throw underflow();
	return root()->max_y();
}

//find the sum of x-value of the root and all its children by recursively going through the whole tree using the sum_x method done in Quadtree_node.h
template <typename T>
T Quadtree<T>::sum_x() const {
	if (empty()) return 0;
	return root()->sum_x();
}

//find the sum of y-value of the root and all its children by recursively going through the whole tree using the sum_y method done in Quadtree_node.h
template <typename T>
T Quadtree<T>::sum_y() const {
	if (empty()) return 0;
	return root()->sum_y();
}

//return the address of the root
template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
	if (empty()) return 0;
	return tree_root;
}

//Check if the given x and y value exist in the root and all its children by recursively using the member() method done in Quadtree_node.h
template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
	if (this == 0) {
		return false;
	}
	return root()->member(x, y);
}

//insert the given x and y value in the appropriate place in the tree by recursively using the insert() method done in Quadtree_node.h. Count(size) is increased everytime a set of x and y value is inserted
template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
	if (root() == 0){
		tree_root = new Quadtree_node<T>(x, y);
		count++;
	}
	else{
		if (tree_root -> insert(x,y) == true)
			count++;
	}
}

//Clears the root and sets count(size) to zero
template <typename T>
void Quadtree<T>::clear() {
	if (root() != 0){
		root()->clear();	
	}
	tree_root = 0;
	count = 0;
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
