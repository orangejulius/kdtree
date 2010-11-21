#ifndef KDNODE_H
#define KDNODE_H

#include <Eigen/Core>
#include <iostream>

#include "NeighborList.h"

using std::cout;
using std::endl;

using Eigen::Matrix;

/**
 * Class KDNode
 * Represents a single node in a kd-tree
 * @tparam T	the type of object stored in this node
 * @tparam numAxes the number of axes (number of dimensions) in the search space
 */
template <class T, int numAxes>
class KDNode
{
	typedef Matrix<double, numAxes, 1> Point;
public:
	/**
	* Construct a kd-tree node
	* @param data	the object to store in this nodes
	* @param point 	the N-dimensional location of this node
	*/
	KDNode(T data, Point point): data(data), point(point) {
		left = 0;
		right = 0;
	}

	/**
	 * Print details about this node
	 * @param depth		the depth at this level
	 * @param recursive	if true, print child nodes using in order traversal
	 */
	void print(int depth = 0, bool recursive = true) const {
		if (recursive && left) left->print(depth + 1);
		cout << "Point: Depth: "<<depth<<endl;
		cout << point <<endl;
		if (recursive && right) right->print(depth + 1);
	}

	/// Return true if this node is a leaf (has no children)
	bool isLeaf() const {
		return (left == 0) && (right == 0);
	}

	/// Return the data object stored in this node
	T getData() const {
		return data;
	}

	/// Returns the coordinates of this node
	Point getPoint() const{
		return point;
	}

	/// Returns the right child pointer of this node
	KDNode* getRight() const {
		return right;
	}

	/// Returns the lft child pointer of this node
	KDNode* getLeft() const {
		return left;
	}

	/// Set the right child node
	void setRight(KDNode* newNode) {
		right = newNode;
	}

	/// Set the left child node
	void setLeft(KDNode* newNode) {
		left = newNode;
	}

	/**
	* Perform a recursive search of this node and child nodes.
	* Return the nearest neighbor to the given point.
	* @param[in,out] neighborList		the list of the current n best neighbors
	* @param searchPoint		the point for which to find the nearest neighbor
	* @param depth		the current depth of the search
	*/
	void nearestNeighbor(NeighborList<KDNode<T, numAxes>* >& neighborList, Point searchPoint, int depth = 0) {
		neighborList.testNeighbor(this, (point - searchPoint).squaredNorm());

		KDNode* nearChild = 0;
		KDNode* farChild = 0;

		int axis = depth % numAxes;
		if (searchPoint[axis] > point[axis]) {
			nearChild = right;
			farChild = left;
		} else {
			nearChild = left;
			farChild = right;
		}

		if (nearChild) {
			nearChild->nearestNeighbor(neighborList, searchPoint, depth + 1);
		}

		double hyperSphereRadius = searchPoint[axis] - point[axis];
		hyperSphereRadius = hyperSphereRadius * hyperSphereRadius;
		if (farChild && hyperSphereRadius < neighborList.getBiggestDistance()) {
			farChild->nearestNeighbor(neighborList, searchPoint, depth + 1);
		}
	}

private:
	/// The object stored in this node
	T data;

	/// This node's left child node
	KDNode* left;

	/// This Node's right child node
	KDNode* right;

	/// The coordinates of this node
	Point point;
};

#endif
