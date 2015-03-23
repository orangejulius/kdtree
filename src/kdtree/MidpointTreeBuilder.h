#ifndef MIDPOINTTREEBUILDER_H
#define MIDPOINTTREEBUILDER_H

#include <Eigen/Core>
#include <limits>
#include <list>

#include "Item.h"
#include "PointSplitNode.h"

using Eigen::Matrix;
using Eigen::Vector2d;
using std::list;

namespace KDTree {
	template <class T, int numAxes>
	class MidpointTreeBuilder {
		public:
			PointSplitNode<T, numAxes>* build(list<Item<T, numAxes> > items) {
				return recursiveSplit(items);
			}

		private:
			PointSplitNode<T, numAxes>* recursiveSplit(list<Item<T, numAxes> > items, int depth = 0) {
				if (items.size() == 0) {
					return 0;
				}

				int axis = depth % numAxes;

				double midpoint = getMidpoint(items, axis);

				list<Item<T, numAxes> > left;
				list<Item<T, numAxes> > right;
				Item<T, numAxes> middle(0, Vector2d(0, 0));

				partition(items, left, right, middle, midpoint, axis);

				PointSplitNode<T, numAxes>* node = new PointSplitNode<T, numAxes>(middle.item, middle.point);

				node->setLeft(recursiveSplit(left, depth + 1));
				node->setRight(recursiveSplit(right, depth + 1));

				return node;
			}

		private:
			double getMidpoint(list<Item<T, numAxes> > items, int axis) {
				double high = std::numeric_limits<double>::infinity() * -1;
				double low = std::numeric_limits<double>::infinity();

				typename list<KDTree::Item<T, numAxes> >::iterator it;
				for (it = items.begin(); it != items.end(); it++) {
					if (it->point[axis] < low) {
						low = it->point[axis];
					}
					if (it->point[axis] > high) {
						high = it->point[axis];
					}
				}
				return (high + low) / 2.0;
			}

			void partition(list<Item<T, numAxes> > items, list<Item<T, numAxes> >& left, list<Item<T, numAxes> >& right, Item<T, numAxes>& middle, const double midpoint, const int axis) {
				typename list<KDTree::Item<T, numAxes> >::iterator it;
				for (it = items.begin(); it != items.end(); it++) {
					if (it->point[axis] < midpoint) {
						left.push_back(*it);
					} else {
						if (right.size() > 0 && it->point[axis] < right.front().point[axis]) {
							right.push_front(*it);
						} else {
							right.push_back(*it);
						}
					}
				}

				middle = right.front();
				right.pop_front();
			}
	};
}

#endif
