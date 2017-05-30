#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/*****************************************
 * UW User ID:  anavid
  University of Waterloo
 * Calender Term of Submission:  (Fall) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include <algorithm>

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
	//Lists all the private variables to be used in the program
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;
	//Lists all the public variables to be used in the program
	public:
		Quadtree_node( T const & = T(), T const & = T() );

		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

	friend class Quadtree<T>;
};

//constructor initializes all the variables to be used in the program
template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

//returns the x-value of the current node
template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
}

//returns the y-value of the current node
template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}

//returns pointer to the north-west children of the node
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

//returns pointer to the north-east children of the node
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

//returns pointer to the south-west children of the node
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}

//returns pointer to the south-east children of the node
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

//Returns the minimum value of x of the current node and its children
template <typename T>
T Quadtree_node<T>::min_x() const {
	//if current node has no value, returns zero
	if (this == 0) return 0;
	
	//If both children that have lesser x-values than the current node does not exist, return the x-value of the current node
	if(south_west == 0 && north_west == 0) return x_value;
	
	//If both children that have lesser x-values than the current node exist, find the minimum of the x-values of the two children nodes using recursion
	else if (south_west != 0 && north_west != 0)
		return std::min(south_west->min_x(), north_west->min_x());
	
	//if only one of the children that has lesser x-value than the current node exist, find the minimum x-value of the child and its children using recursion
	else if (south_west == 0 && north_west != 0)
		return north_west->min_x();
	else if (south_west != 0 && north_west == 0)
		return south_west->min_x();
}

//Returns the minimum value of y of the current node and its children
template <typename T>
T Quadtree_node<T>::min_y() const {
	if (this == 0) return 0;
	if (south_west == 0 && south_east == 0) return y_value;
	else if (south_west != 0 && south_east != 0)
		return std::min(south_west->min_y(), south_east->min_y());
	else if (south_west == 0 &&south_east != 0)
		return south_east->min_y();
	else if (south_west != 0 && south_east == 0)
		return south_west->min_y();
}

//Returns the maximum value of x of the current node and its children
template <typename T>
T Quadtree_node<T>::max_x() const {
	if (this == 0) return 0;
	if(north_east == 0 && south_east == 0) return x_value;
	else if (north_east != 0 && south_east != 0)
		return std::max(north_east->max_x(), south_east->max_x());
	else if (north_east == 0 && south_east != 0)
		return south_east->max_x();
	else if (north_east != 0 && south_east == 0)
		return north_east->max_x();
}

//Returns the maximum value of y of the current node and its children
template <typename T>
T Quadtree_node<T>::max_y() const {
	if (this == 0) return 0;
	if(north_east == 0 && north_west == 0) return y_value;
	else if (north_east != 0 && north_west != 0)
		return std::max(north_east->max_y(), north_west->max_y());
	else if (north_east == 0 && north_west != 0)
		return north_west->max_y();
	else if (north_east != 0 && north_west == 0)
		return north_east->max_y();
	
}

//Returns the sum of the x-values of the current node and all its childrens
template <typename T>
T Quadtree_node<T>::sum_x() const {
	//if the current node is zero, it can't have any children. Therefore, the sum is 0
	if ( this == 0 ) {
		return 0;
	} 

	//To find the sum, add the sum of the x-values of all the children nodes and the children of those children, etc using a recursive function
	else {
		return north_east->sum_x() + south_east->sum_x() + north_west->sum_x() + south_west->sum_x() + x_value;
	}
}

//Returns the sum of the y-values of the current node and all its childrens
template <typename T>
T Quadtree_node<T>::sum_y() const {
	if (this == 0) {
		return 0;
	}
	else {
		return north_east->sum_y() + south_east->sum_y() + north_west->sum_y() + south_west->sum_y() + y_value;
	}
}

//Check if the given x and y value are the same as the x and y value of the node or its children
template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	//If node is 0, return false because there are no children either
	if ( this == 0 ) {
		return false;
	}
	
	//If the x and y value matches the x and y value of the current node, return true
	if (x==x_value && y==y_value) return true;
	
	//if x is less than x-value of current node and y is less than y-value of current node, check south-west children. If south-west children is zero, it means the x and y-value can't exist in the tree.
	//If its not zero, check the children of the south west node recursively. the same concept is applied to the other three children of the main node.
	if (x<x_value && y<y_value){
		if (south_west==0){
			return false;
		}
		else 
			return south_west -> member(x,y);
	}
	else if (x<x_value && y>y_value){
		if (north_west==0){
			return false;
		}
		else 
			return north_west -> member(x,y);
	}
	else if (x>x_value && y>y_value){
		if (north_east==0){
			return false;
		}
		else 
			return north_east -> member(x,y);
	}
	else if (x>x_value && y<y_value){
		if (south_east==0){
			return false;
		}
		else 
			return south_east -> member(x,y);
	}
	//Default value is to return false if none of the above conditions are met, which is highly unlikely
	return false;
}

//inserts the given x and y value in the quad tree under the current node in the appropriate place
template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
	//if the given x and y value already exists, returns false as insertion can't be done
	if (x==x_value && y==y_value) return false;
	
	//if x is less than x - value of current node and y is less than y - value of current node, check south - west children.If south - west children is zero, insert the x and y values in the south west children.
	//If south west childrne is not zero, insert to a children of south west node recursively. This concept is also used in the case of the other three children of the main node.
	else if (x<x_value && y<y_value){
		if (south_west==0){
			south_west=new Quadtree_node<T>(x,y);
			return true;
		}
		else 
			return south_west -> insert(x,y);
	}
	else if (x<x_value && y>y_value){
		if (north_west==0){
			north_west=new Quadtree_node<T>(x,y);
			return true;
		}
		else 
			return north_west -> insert(x,y);
	}
	else if (x>x_value && y>y_value){
		if (north_east==0){
			north_east=new Quadtree_node<T>(x,y);
			return true;
		}
		else 
			return north_east -> insert(x,y);
	}
	else if (x>x_value && y<y_value){
		if (south_east==0){
			south_east=new Quadtree_node<T>(x,y);
			return true;
		}
		else 
			return south_east -> insert(x,y);
	}
	//Default value is to return false if none of the above conditions are met, which is highly unlikely
	return false;
}

//Clears the children of the nodes, and then deleted the currrent node
template <typename T>
void Quadtree_node<T>::clear() {
	if (sw()!= 0){
		south_west -> clear();
		south_west = 0;
	}
	if (nw() != 0){
		north_west->clear();
		north_west = 0;
	}
	if (se() != 0){
		south_east->clear();
		south_east = 0;
	}
	if (ne() != 0){
		north_east->clear();
		north_east = 0;
	}
	delete this;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
