#ifndef KDNODE_H
#define KDNODE_H

#include <Eigen/Core>
#include <iostream>

using std::cout;
using std::endl;

using Eigen::Vector2d;

/**
 * Class KDNode
 * Represents a single node in a kd-tree
 * @tparam T	the type of object stored in this node
 */
template <class T>
class KDNode
{
public:
	/**
	* Construct a kd-tree node
	* @param data	the object to store in this node
	* @param point 	the 2d location of this node
	* @param depth 	the depth of this node in the tree
	* @param numAxes 	the number of axes in this tree (always 2 currently)
	* @param parent 	the parent node of this node
	*/
	KDNode(T data, Vector2d point, unsigned depth, unsigned numAxes, KDNode* parent): data(data), point(point), depth(depth), numAxes(numAxes), parent(parent) {
		left = 0;
		right = 0;
	}

	/**
	 * Insert a point as this nodes child
	 * @param point 	the new point to add as a child
	 * @return KDNode* 	the pointer to the new node
	 */
	KDNode* insertPoint(Vector2d newPoint, T payload) {
		int axis = depth % numAxes;//the axis by which points will be compared
		if (newPoint[axis] > point[axis]) {
			//point goes to right node
			if (right) {
				return right->insertPoint(newPoint, payload);
			} else {
				right = new KDNode<T>(payload, newPoint, depth + 1, numAxes, this);
				return right;
			}
		} else {
			//point goes to left node
			if (left) {
				return left->insertPoint(newPoint, payload);
			} else {
				left = new KDNode<T>(payload, newPoint, depth + 1, numAxes, this);
				return left;
			}
		}
	}

	/**
	 * Print details about this node
	 * @param recursive	if true, print child nodes using in order traversal
	 */
	void print(bool recursive = true) const {
		if (recursive && left) left->print();
		cout << "Point: "<<point[0]<<","<<point[1]<<" Depth: "<<depth<<endl;
		if (recursive && right) right->print();
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
	Vector2d getPoint() const {
		return point;
	}

	/// Returns the depth of this node
	int getDepth() const {
		return depth;
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
	* @param point		the point for which to find the nearest neighbor
	* @return Vector2d	the location of the nearest neighbor of point
	*/
	Vector2d nearestNeighbor(Vector2d searchPoint, Vector2d best = Vector2d(99999,99999)) const {
		if ((point - searchPoint).squaredNorm() < (best - searchPoint).squaredNorm()) {
			best = point;
		}

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
			best = nearChild->nearestNeighbor(searchPoint, best);
		}

		double hyperSphereRadius = searchPoint[axis] - point[axis];
		if (farChild && hyperSphereRadius < (best - searchPoint).norm()) {
			best = farChild->nearestNeighbor(searchPoint, best);
		}

		return best;
	}

private:
	/// The object stored in this node
	T data;

	/// The depth of this node in the tree
	int depth;

	/// The number of axes used for comparison
	int numAxes;

	/// This node's parent node
	KDNode* parent;

	/// This node's left child node
	KDNode* left;

	/// This Node's right child node
	KDNode* right;

	/// The coordinates of this node
	Vector2d point;
};

#endif
