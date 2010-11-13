#ifndef KDNODE_H
#define KDNODE_H

#include <Eigen/Core>

using Eigen::Vector2d;

/**
 * Class KDNode
 * Represents a single node in a kd-tree
 */
class KDNode
{
public:
	/**
	 * Construct a kd-tree node
	 * @param point 	the 2d location of this node
	 * @param depth 	the depth of this node in the tree
	 * @param numAxes 	the number of axes in this tree (always 2 currently)
	 * @param parent 	the parent node of this node
	 */
	KDNode(Vector2d point, unsigned depth, unsigned numAxes, KDNode* parent);

	/**
	 * Insert a point as this nodes child
	 * @param point 	the new point to add as a child
	 * @return KDNode* 	the pointer to the new node
	 */
	KDNode* insertPoint(Vector2d point);

	/**
	 * Print details about this node
	 * @param recursive	if true, print child nodes using in order traversal
	 */
	void print(bool recursive = true) const;

	/// Return true if this node is a leaf (has no children)
	bool isLeaf() const {
		return (left == 0) && (right == 0);
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

private:
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
