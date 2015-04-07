#ifndef PLANESPLITNODE_H
#define PLANESPLITNODE_H

#include <Eigen/Core>

#include "kdtree/Item.h"

using Eigen::Matrix;

namespace KDTree {
	template<class T, int numAxes>
		class PlaneSplitNode
		{
			typedef Matrix<double, numAxes, 1> Point;
			public:

			// constructor for internal node
			PlaneSplitNode(int axis, double partition, PlaneSplitNode* left = 0, PlaneSplitNode* right = 0): axis(axis), partition(partition), left(left), right(right) {};

			// constructor for leaf node
			PlaneSplitNode(list<Item<T, numAxes> > items): items(items) {
				partition = 0.0;
				axis = 0;
				left = 0;
				right = 0;
			}

			bool isLeaf() const {
				return (left == 0) && (right == 0);
			}

			PlaneSplitNode* getLeft() const {
				return left;
			}

			PlaneSplitNode* getRight() const {
				return right;
			}

			int getAxis() const {
				return axis;
			}

			double getPartition() const {
				return partition;
			}

			list<Item<T, numAxes> > getItems() const {
				return items;
			}

			private:
			PlaneSplitNode* left;
			PlaneSplitNode* right;

			int axis;
			double partition;

			list<Item<T, numAxes> > items;
		};

}

#endif
