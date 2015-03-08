#ifndef KDTREE_H
#define KDTREE_H

#include <Eigen/Core>
#include <Eigen/Array>
#include <list>

#include "KDNode.h"

using Eigen::Vector2d;
using std::list;

/**
 * Class KDTree
 * Represents an entire kd-tree.
 * @tparam T	the type of items stored in nodes of this tree
 * @tparam numAxes	the number of axes to compare (the number of dimensions in the search space)
 */
template <class T, int numAxes=2>
class KDTree
{
	typedef Matrix<double, numAxes, 1> Point;
public:
	/**
	 * Construct a new kd-tree
	 */
	KDTree() {
		root = 0;
		numNodes = 0;
		maxDepth = 0;
	}

	int getMaxDepth() {
		return maxDepth;
	}

	/**
	 * Insert an N-dimensional point into the kd-tree
	 * @param newPoint	the N-dimensional point to add
	 * @param data		the data object to store in the node
	 */
	void insertPoint(Point newPoint, T data) {
		//if the tree already has an element in it, just add the point
		if (root) {
			KDNode<T, numAxes>* currentNode = root;
			int depth = 0;
			KDNode<T, numAxes>* newNode = 0;
			while (newNode == 0) {
				int axis = depth % numAxes;//the axis by which points will be compared
				if (newPoint[axis] > currentNode->getPoint()[axis]) {
					//point goes to right node
					if (currentNode->getRight()) {
						currentNode = currentNode->getRight();
					} else {
						newNode = new KDNode<T, numAxes>(data, newPoint);
						currentNode->setRight(newNode);
					}
				} else {
					if (currentNode->getLeft()) {
						currentNode = currentNode->getLeft();
					} else {
						newNode = new KDNode<T, numAxes>(data, newPoint);
						currentNode->setLeft(newNode);
					}
				}
				depth++;
			}

			//keep track of the max depth
			if (depth > maxDepth) {
				maxDepth = depth;
			}
		} else {
			//otherwise create the root node of the tree
			root = new KDNode<T, numAxes>(data, newPoint);
		}
		//keep track of the number of nodes inserted
		numNodes++;
	}

	/**
	 * Print details about the entire tree
	 */
	void print() const {
		if (root) {
			root->print();
			cout << "Total nodes: "<<numNodes<<endl;
			cout << "Max depth: " << maxDepth << endl;
		} else {
			cout << "Tree is empty\n";
		}
	}

	/**
	* Find the n nearest neighbors of a point.
	* For a point already in the tree, the 1st nearest neighbor is always that point
	* @param point		the point for which to find the nearest neighbors
	* @param numNeighbors	the number of neighbors to retrieve.
	* @return list<KDNode<T, numAxes>* >	a list of the n nearest neighbor KDNodes
	*/
	list<KDNode<T, numAxes>* > nearestNeighbor(Point point, unsigned int numNeighbors = 1) {
		NeighborList<KDNode<T, numAxes>* > neighborList(numNeighbors);
		root->nearestNeighbor(neighborList, point);

		return neighborList.getList();
	}

private:
	/// the root node of the kd tree
	KDNode<T, numAxes>* root;

	/// the total number of nodes in the tree
	int numNodes;

	/// the maximum depth of the tree
	int maxDepth;
};

#endif // KDTREE_H
