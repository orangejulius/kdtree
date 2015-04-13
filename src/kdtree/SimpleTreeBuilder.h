#ifndef SIMPLETREEBUILDER_H
#define SIMPLETREEBUILDER_H

#include <Eigen/Core>

#include "Item.h"
#include "kdtree/PlaneSplitNode.h"

using Eigen::Matrix;

namespace KDTree {
	template <class T, int numAxes>
	class SimpleTreeBuilder {
		public:
			typedef Matrix<double, numAxes, 1> Point;
			PointSplitNode<T, numAxes>* build(list<Item<T, numAxes> > items) {
				if (items.size() == 0) {
					return 0;
				}
				PointSplitNode<T, numAxes>* root = 0;

				typename list<KDTree::Item<T, numAxes> >::iterator it;
				for(it = items.begin(); it != items.end(); it++) {
					PointSplitNode<T, numAxes>* node = new PointSplitNode<T, numAxes>(it->item, it->point);
					if (root) {
						recursiveInsert(root, node);
					} else {
						root = node;
					}
				}
				return root;
			};

			PlaneSplitNode<T, numAxes>* build_plane_split(list<Item<T, numAxes> > items, unsigned int maxLeafSize) {
				return recursive_insert(items, maxLeafSize);
			}

		private:
			void recursiveInsert(PointSplitNode<T, numAxes>* root, PointSplitNode<T, numAxes>* node, int depth = 0) {
				int axis = depth % numAxes;
				if (node->getPoint()[axis] > root->getPoint()[axis]) {
					if (root->getRight()) {
						recursiveInsert(root->getRight(), node, depth + 1);
					} else {
						root->setRight(node);
					}
				} else {
					if (root->getLeft()) {
						recursiveInsert(root->getLeft(), node, depth + 1);
					} else {
						root->setLeft(node);
					}
				}
			}

			PlaneSplitNode<T, numAxes>* recursive_insert(const list<Item<T, numAxes> > items, unsigned int maxLeafSize, int depth = 0) {
				if (items.size() <= maxLeafSize) {
					return new PlaneSplitNode<T, numAxes>(items);
				} else {
					int axis = depth % numAxes;
					typename list<Item<T, numAxes > >::const_iterator partition_item = items.begin();
					double partition;
					list<Item<T, numAxes> > leftItems;
					list<Item<T, numAxes> > rightItems;

					while (leftItems.size() == 0 || rightItems.size() == 0) {
						partition = partition_item->point[axis];
						leftItems.clear();
						rightItems.clear();
						partition_items(axis, partition, items, leftItems, rightItems);
						partition_item++;
					}
					PlaneSplitNode<T, numAxes>* left = recursive_insert(leftItems, maxLeafSize, depth + 1);
					PlaneSplitNode<T, numAxes>* right = recursive_insert(rightItems, maxLeafSize, depth + 1);
					return new PlaneSplitNode<T, numAxes>(axis, partition, left, right);
				}
			}

			void partition_items(int axis, double partition, const list<Item<T, numAxes> > items, list<Item<T, numAxes > > &left, list<Item<T, numAxes> > &right) {
				typename list<Item<T, numAxes> >::const_iterator it;
				for(it = items.begin(); it != items.end(); it++) {
					if (it->point[axis] >= partition) {
						right.push_back(*it);
					} else {
						left.push_back(*it);
					}
				}
			}

	};
}

#endif
