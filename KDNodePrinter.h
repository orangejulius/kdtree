#ifndef KDNODEPRINTER_H
#define KDNODEPRINTER_H

#include <iostream>

#include "KDNode.h"

template <class T, int numAxes>
class KDNodePrinter {

	public:
		void print(KDNode<T, numAxes> node, std::ostream &out) {
			out<<"(";

			for (int i = 0; i < numAxes; i++) {
				out<<node.getPoint()[i];
				if (i + 1 < numAxes) {
					out<<", ";
				}
			}
			out<<") ";
			out<<node.getData()<<endl;
		}
};

#endif
