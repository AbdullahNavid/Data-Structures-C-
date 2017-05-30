#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/*****************************************
 * UW User ID:  anavid
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	private:
		static const double INF;
		// your choice
		double **adj_matrix;
		int n_vertices;
		int n_edges;
		double m;
		
	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();
		int degree(int n) const;
		
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();


// Enter definitions for all public functions here
	Weighted_graph::Weighted_graph(int size) :
		//initializes the variables and arrays to be used in the methods
		n_vertices(0), n_edges(0),
		m(size),
		adj_matrix(new double *[size]){
		for (int i = 0; i < m; ++i) {
			adj_matrix[i] = new double[size];
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; j++){
				adj_matrix[i][j] = INF;
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; j++){
				if (i == j)
					adj_matrix[i][j] = 0;
			}
		}
	}


	std::ostream &operator << (std::ostream &out, Weighted_graph const &graph) {
		// Your implementation

		return out;
	}

	//Destructor deletews the arrays
	Weighted_graph::~Weighted_graph() {
		for (int i = 0; i < m; ++i) {
			delete[] adj_matrix[i];
		}
		delete[] adj_matrix;
	}

	int Weighted_graph::degree(int obj) const {
			int degrees = 0;
			for (int i = 0; i < m; i++){
				if (adj_matrix[obj][i] != INF)
					degrees++;
			}
			if (degrees == 0)
				throw illegal_argument();
			return degrees;
		}

	int Weighted_graph::edge_count() const {
			return n_edges;
		}

	double Weighted_graph::adjacent(int obj, int obj1) const {
			if (obj == obj1)
				return 0;
			if (adj_matrix[obj][obj1] == INF)
				return INF;
			if (obj > m || obj1 > m)
				throw illegal_argument();
			return adj_matrix[obj][obj1];
		}

	bool Weighted_graph::is_connected() const {
		int n_connections;
		int max;
		int a = -1;
		int b = -1;
		int c = -1;
		int d = -1;
		for (int i = 0; i < m; i++){
			n_connections = 0;
			for (int j = 0; j < m; j++){
				if (adj_matrix[i][j] != INF && i != j){
					n_connections++;
				}
			}
			if (n_connections == 0)
				return false;
			if (n_connections == 1){
				if (a == -1)
					a = i;
				else if (b == -1)
					b = i;
				else if (c == -1)
					c = i;
				else if (d == -1)
					d = i;
				else
					return false;
			}
		}
		if (a != -1 && b != -1 && c==1 && d==1){
			if (adj_matrix[a][b] != INF)
				return false;
		}
		else if (a != -1 && b != -1 && c != 1 && d == 1){
			if (adj_matrix[a][b] != INF)
				return false;
			else if (adj_matrix[a][c] != INF)
				return false;
			else if (adj_matrix[b][c] != INF)
				return false;
		}
		else if (a != -1 && b != -1 && c != 1 && d == 1){
			if (adj_matrix[a][b] != INF)
				return false;
			else if (adj_matrix[a][c] != INF)
				return false;
			else if (adj_matrix[b][c] != INF)
				return false;
			else if (adj_matrix[a][d] != INF)
				return false;
			else if (adj_matrix[d][c] != INF)
				return false;
			else if (adj_matrix[b][d] != INF)
				return false;
		}
		return true;
		
	}


	double Weighted_graph::minimum_spanning_tree(int obj) const {
		double min = 0;
		double minimum = 0;
		for (int i = 0; i < m; i++){
			minimum = 1000;
			for (int j = 0; j < m; j++){
				if (adj_matrix[obj][j] != INF || adj_matrix[obj][i] != INF){
					if (adj_matrix[i][j] < minimum && i!=j)
						minimum = adj_matrix[i][j];
				}
		}
			if (minimum != 1000 && minimum >0 && minimum != INF)
				min = min + minimum;
		}
		return min;
	}

	void Weighted_graph::insert(int obj, int obj1, double weight){
			if (weight < 0 || weight == INF)
				throw illegal_argument();
			else if (obj == obj1)
				throw illegal_argument();
			else if (weight == 0){
				adj_matrix[obj][obj1] = INF;
				adj_matrix[obj1][obj] = INF;
				n_edges--;
			}
			else if (adj_matrix[obj][obj1] != INF){
				adj_matrix[obj][obj1] = weight;
				adj_matrix[obj1][obj] = weight;
				}
			else{
				adj_matrix[obj][obj1] = weight;
				adj_matrix[obj1][obj] = weight;
				n_edges++;
				}
		}
#endif
