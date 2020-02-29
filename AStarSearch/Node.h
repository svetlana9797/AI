#ifndef NPUZZLE_NODE_H
#define NPUZZLE_NODE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <cstring>

using namespace std;

class Node {
public:
	int **A = nullptr;
//	int cost;
//default constructor
	Node() {
//		emptyNode = true;
		A = new int *[3];
		for (int i = 0; i < 3; ++i) {
			A[i] = new int[3];
			memset(A[i], 0, 3 * sizeof(A[0][0]));
		}

//		cost = 0;
	}

//constructor from a node
	Node(const Node &node) {
		this->~Node();
		A = new int *[3];
		for (int i = 0; i < 3; ++i) {
			A[i] = new int[3];
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				A[i][j] = node.A[i][j];
			}
		}
//		this->cost = node.cost;
	}

	//operator =
	Node &operator=(const Node &node) {
		this->~Node();
		A = new int *[3];
		for (int i = 0; i < 3; ++i) {
			A[i] = new int[3];
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				A[i][j] = node.A[i][j];
			}
		}
//		cost = node.cost;
		return *this;
	}

	//destructor
	~Node() {
		if (A == nullptr) return;
		for (int i = 0; i < 3; ++i) {
			delete A[i];
		}
		delete[] A;
		A = nullptr;
	}

	bool operator==(const Node &other) const {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (A[i][j] != other.A[i][j]) return false;
		return true;
	}

	bool operator!=(const Node &other) const {
		return !(*this == other);
	}

	bool operator<(const Node &other) const {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (A[i][j] < other.A[i][j]) return true;
				else if (A[i][j] == other.A[i][j]) continue;
				else return false;
			}
		}
		return false;
	}

};
struct NodeInfo {
	bool isClosed;
	int cost;
};

#endif //NPUZZLE_NODE_H
