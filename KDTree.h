#ifndef KDTREE_H
#define KDTREE_H

#include <Eigen/Core>

using Eigen::Vector2d;

class KDNode;

/**
 * Class KDTree
 * Represents an entire kd-tree.
 */
class KDTree
{
public:
	/**
	 * Construct a new kd-tree
	 */
	KDTree();

	/**
	 * Insert a 2d point into the kd-tree
	 * @param newPoint	the 2d point to add
	 */
	void insertPoint(Vector2d newPoint);

	/**
	 * Print details about the entire tree
	 */
	void print() const;

private:
	/// the root node of the kd tree
	KDNode* root;

	/// the total number of nodes in the tree
	int numNodes;

	/// the maximum depth of the tree
	int maxDepth;

	/// the number of axes used for comparison in this tree
	int numAxes;
};

#endif // KDTREE_H
