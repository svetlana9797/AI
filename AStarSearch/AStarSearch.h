#include "Node.h"

#ifndef NPUZZLE_ASTARSEARCH_H
#define NPUZZLE_ASTARSEARCH_H

//Node info stores information about the Node's cost, if it is closed and his parent
//struct NodeInfo {
//	bool isClosed;
//	int cost;
//	int parent;
//
//	bool operator==(const NodeInfo &o) const {
//		return parent == o.parent &&
//		       cost == o.cost;
//	}
//
//	bool operator!=(const NodeInfo &o) const {
//		return !(o == *this);
//	}
//};
//
//	 bool getZeroPos(const Node &node, int &zX, int &zY) {
//		zX = zY = -1;
//		for (int i = 0; i < 3; i++) {
//			for (int j = 0; j < 3; j++)
//				if (!node.A[i][j]) {
//					zX = i, zY = j;
//					return true;
//				}
//		}
//		return false;
//	}

#endif //NPUZZLE_ASTARSEARCH_H
