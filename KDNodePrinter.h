#ifndef KDNODEPRINTER_H
#define KDNODEPRINTER_H

#include <iostream>

#include "KDNode.h"

template <class T, int numAxes>
class KDNodePrinter {

	public:
		void print(KDNode<T, numAxes> node, std::ostream &out) {
			out<<node.getPoint()<<endl<<node.getData()<<endl;
		}
};

#endif
