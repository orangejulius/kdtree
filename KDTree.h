#ifndef KDTREE_H
#define KDTREE_H

#include <Eigen/Core>

#include "KDNode.h"

using Eigen::Vector2d;

/**
 * Class KDTree
 * Represents an entire kd-tree.
 * @tparam T	the type of items stored in nodes of this tree
 */
template <class T>
class KDTree
{
public:
	/**
	 * Construct a new kd-tree
	 */
	KDTree() {
		root = 0;
		numNodes = 0;
		maxDepth = 0;
		numAxes = 2;//for now this only handles the 2D tree case
	}

	/**
	 * Insert a 2d point into the kd-tree
	 * @param newPoint	the 2d point to add
	 * @param data		the data object to store in the node
	 */
	void insertPoint(Vector2d newPoint, T data) {
		//if the tree already has an element in it, just add the point
		if (root) {
			KDNode<T>* newnode = root->insertPoint(newPoint, data);

			//keep track of the max depth
			if (newnode->getDepth() > maxDepth) {
				maxDepth = newnode->getDepth();
			}
		} else {
			//otherwise create the root node of the tree
			root = new KDNode<T>(data, newPoint, 0, numAxes, 0);
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
	* Find the nearest neighbor of a point
	* @param point		the point for which to find the nearest neighbor
	* @return Vector2d	the location of the nearest neighbor of point
	*/
	Vector2d nearestNeighbor(Vector2d point) const {
		Vector2d nn = root->nearestNeighbor(point);
		cout<<nn<<endl;
		return nn;
	}

private:
	/// the root node of the kd tree
	KDNode<T>* root;

	/// the total number of nodes in the tree
	int numNodes;

	/// the maximum depth of the tree
	int maxDepth;

	/// the number of axes used for comparison in this tree
	int numAxes;
};

#endif // KDTREE_H
