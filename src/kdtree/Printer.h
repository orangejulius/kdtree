#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>

using std::endl;
using std::ostream;

#include "PlaneSplitNode.h"
#include "PointSplitNode.h"

namespace KDTree {
	template <class T, int numAxes>
	class Printer {
			typedef Matrix<double, numAxes, 1> Point;
		public:
		void print(PointSplitNode<T, numAxes>* node, ostream &out) {
			if (node->getLeft()) {
				print(node->getLeft(), out);
			}

			print_current(node, out);

			if (node->getRight()) {
				print(node->getRight(), out);
			}
		}

		void print(PlaneSplitNode<T, numAxes>* node, ostream &out) {
			if (node->getLeft()) {
				print(node->getLeft(), out);
			}

			if(node->isLeaf() && node->getItems().size() > 0) {
				list<Item<T, numAxes> > items = node->getItems();
				typename list<Item<T, numAxes> >::iterator it;
				for (it = items.begin(); it != items.end(); it++) {
					out<<it->item<<" ";
					print_point(it->point, out);
				}
				out<<endl;
			} else {
				out<<node->getAxis()<<" "<<node->getPartition()<<endl;
			}

			if (node->getRight()) {
				print(node->getRight(), out);
			}
		}

		private:
		void print_current(PointSplitNode<T, numAxes>* node, ostream &out) {
			print_point(node->getPoint(), out);
			out<<node->getData()<<endl;
		}

		void print_point(Point p, ostream &out) {
			out<<"(";
			for (int i = 0; i < numAxes; i++) {
				out<<p[i];
				if (i + 1 < numAxes) {
					out<<", ";
				}
			}
			out<<") ";
		}

	};
}

#endif
