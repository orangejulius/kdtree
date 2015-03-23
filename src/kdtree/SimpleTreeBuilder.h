#ifndef SIMPLETREEBUILDER_H
#define SIMPLETREEBUILDER_H

#include <Eigen/Core>

using Eigen::Matrix;

namespace KDTree {
	template <class T, int numAxes>
	struct Item {
		typedef Matrix<double, numAxes, 1> Point;
		Item(T item, Point point): item(item), point(point) {};

		T item;
		Point point;
	};

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

	};
}

#endif
