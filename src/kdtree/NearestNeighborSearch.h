#ifndef NEARESTNEIGHBORSEARCH_H
#define NEARESTNEIGHBORSEARCH_H

#include "PlaneSplitNode.h"
#include "PointSplitNode.h"

using std::list;

namespace KDTree {

	template <class T, int numAxes>
	class NearestNeighborSearch{
		public:
			typedef Matrix<double, numAxes, 1> Point;
			list<T> search(const PointSplitNode<T, numAxes> tree, Point searchPoint, int numResults = 1) {
				NeighborList<T> results(numResults);

				recursiveSearch(results, &tree, searchPoint);

				return results.getList();
			};

			list<T> search(const PlaneSplitNode<T, numAxes> tree, Point searchPoint, int numResults = 1) {
				NeighborList<T> results(numResults);

				recursiveSearch(results, &tree, searchPoint);

				return results.getList();
			}

		private:
			void recursiveSearch(NeighborList<T>& results, const PointSplitNode<T, numAxes>* tree, Point searchPoint, int depth = 0) {
				Point point = tree->getPoint();
				double squaredDistance = (point - searchPoint).squaredNorm();
				results.testNeighbor(tree->getData(), squaredDistance);

				PointSplitNode<T, numAxes>* nearChild = 0;
				PointSplitNode<T, numAxes>* farChild = 0;

				int axis = depth % numAxes;
				if (searchPoint[axis] > point[axis]) {
					nearChild = tree->getRight();
					farChild = tree->getLeft();
				} else {
					nearChild = tree->getLeft();
					farChild = tree->getRight();
				}

				if (nearChild) {
					recursiveSearch(results, nearChild, searchPoint, depth + 1);
				}

				if (farChild) {
					double hyperSphereRadius = searchPoint[axis] - point[axis];
					double radiusSquared = hyperSphereRadius * hyperSphereRadius;
					if (radiusSquared < results.getLargestDistanceSquared()) {
						recursiveSearch(results, farChild, searchPoint, depth + 1);
					}
				}
			};

			void recursiveSearch(NeighborList<T>& results, const PlaneSplitNode<T, numAxes>* tree, Point searchPoint, int depth = 0) {
				if (tree->getItems().size() > 0) { // leaf node
					typename list<KDTree::Item<T, numAxes> >::const_iterator it;
					int i = 0;
					list<Item<T, numAxes> > items = tree->getItems();
					for(it = items.begin(); it != items.end(); it++) {
						Point point = it->point;
						double squaredDistance = (point - searchPoint).squaredNorm();
						results.testNeighbor(it->item, squaredDistance);
						i++;
					}
				} else { // internal node
					PlaneSplitNode<T, numAxes>* nearChild = 0;
					PlaneSplitNode<T, numAxes>* farChild = 0;

					int axis = tree->getAxis();
					double partition = tree->getPartition();
					if (searchPoint[axis] > partition) {
						nearChild = tree->getRight();
						farChild = tree->getLeft();
					} else {
						nearChild = tree->getLeft();
						farChild = tree->getRight();
					}

					if (nearChild) {
						recursiveSearch(results, nearChild, searchPoint, depth + 1);
					}

					if (farChild) {
						double hyperSphereRadius = searchPoint[axis] - partition;
						double radiusSquared = hyperSphereRadius * hyperSphereRadius;
						if (radiusSquared < results.getLargestDistanceSquared()) {
							recursiveSearch(results, farChild, searchPoint, depth + 1);
						}
					}
				}
			}
	};
}

#endif
