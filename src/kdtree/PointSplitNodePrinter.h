#ifndef KDNODEPRINTER_H
#define KDNODEPRINTER_H

#include <iostream>

using std::endl;
using std::ostream;

#include "PointSplitNode.h"

namespace KDTree {
	template <class T, int numAxes>
	class PointSplitNodePrinter {
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

		private:
		void print_current(PointSplitNode<T, numAxes>* node, ostream &out) {
			out<<"(";

			for (int i = 0; i < numAxes; i++) {
				out<<node->getPoint()[i];
				if (i + 1 < numAxes) {
					out<<", ";
				}
			}
			out<<") ";
			out<<node->getData()<<endl;
		}
	};
}

#endif
