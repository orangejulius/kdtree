#ifndef ITEM_H
#define ITEM_H

#include <Eigen/Core>

using Eigen::Matrix;

namespace KDTree {
	template <class T, int numAxes>
	struct Item {
		typedef Matrix<double, numAxes, 1> Point;
		Item(T item, Point point): item(item), point(point) {};

		T item;
		Point point;
		bool operator==(const Item<T, numAxes> other) const {
			return item == other.item && point == other.point;
		}
	};
}
#endif
