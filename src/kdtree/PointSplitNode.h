#ifndef KDNODE_H
#define KDNODE_H

#include <Eigen/Core>
#include <iostream>

#include "kdtree/NeighborList.h"

using std::cout;
using std::endl;

using Eigen::Matrix;

namespace KDTree {

	/**
	 * Class PointSplitNode
	 * Represents a single node in a kd-tree
	 * @tparam T	the type of object stored in this node
	 * @tparam numAxes the number of axes (number of dimensions) in the search space
	 */
	template <class T, int numAxes>
	class PointSplitNode
	{
		typedef Matrix<double, numAxes, 1> Point;
		public:
		/**
		 * Construct a kd-tree node
		 * @param data	the object to store in this nodes
		 * @param point 	the N-dimensional location of this node
		 */
		PointSplitNode(T data, Point point): data(data), point(point) {
			left = 0;
			right = 0;
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
		PointSplitNode* getRight() const {
			return right;
		}

		/// Returns the lft child pointer of this node
		PointSplitNode* getLeft() const {
			return left;
		}

		/// Set the right child node
		void setRight(PointSplitNode* newNode) {
			right = newNode;
		}

		/// Set the left child node
		void setLeft(PointSplitNode* newNode) {
			left = newNode;
		}

		/**
		 * Perform a recursive search of this node and child nodes.
		 * Return the nearest neighbor to the given point.
		 * @param[in,out] neighborList		the list of the current n best neighbors
		 * @param searchPoint		the point for which to find the nearest neighbor
		 * @param depth		the current depth of the search
		 */
		void nearestNeighbor(NeighborList<PointSplitNode<T, numAxes>* >& neighborList, Point searchPoint, int depth = 0) {
			neighborList.testNeighbor(this, (point - searchPoint).squaredNorm());

			PointSplitNode* nearChild = 0;
			PointSplitNode* farChild = 0;

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
		PointSplitNode* left;

		/// This Node's right child node
		PointSplitNode* right;

		/// The coordinates of this node
		Point point;
	};
}

#endif
