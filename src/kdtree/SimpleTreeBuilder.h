#ifndef SIMPLETREEBUILDER_H
#define SIMPLETREEBUILDER_H

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

				PointSplitNode<T, numAxes>* node = new PointSplitNode<T, numAxes>(items.front().item, items.front().point);
				return node;
			};
	};
}

#endif
