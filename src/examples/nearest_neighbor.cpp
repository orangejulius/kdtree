#include <cstdlib>
#include <fstream>
#include <limits.h>
#include <iostream>
#include <sys/time.h>
#include <vector>

#include "kdtree/PointSplitNode.h"
#include "kdtree/SimpleTreeBuilder.h"
#include "kdtree/MidpointTreeBuilder.h"
#include "kdtree/PointSplitNodePrinter.h"
#include "kdtree/NearestNeighborSearch.h"

using namespace KDTree;

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

typedef Matrix<double, 2, 1> Point;

list<Item<int, 2> > loadFile(int argc, char* argv[])
{
	list<Item<int, 2> > items;
	ifstream file(argv[1]);
	if (file) {
		int maxlines = 100000000;
		if (argc > 2) {
			maxlines = atoi(argv[2]);
		}
		for (int i = 0; i < maxlines; i++) {
			int id;
			double x, y;
			file>>id>>x>>y;
			Item<int, 2> item(id, Point(x, y));
			if (file.eof()) {
				break;
			}
			items.push_back(item);
		}
	}

	return items;
}

void findNeighbors(PointSplitNode<int, 2>* root, list<Item<int, 2> > items)
{
	NearestNeighborSearch<int, 2> search;
	list<Item<int, 2> >::iterator itemIt;
	for (itemIt = items.begin(); itemIt != items.end(); itemIt++) {
		cout<<itemIt->item<<" ";
		list<int> neighbors = search.search(*root, itemIt->point, 4);

		list<int>::iterator it = neighbors.begin();
		it++; // skip first neighbor, it is the point being searched
		for(;it != neighbors.end(); it++) {
			cout<<*it;
			if (it != --neighbors.end()) {
				cout<<",";
			}
		}
		cout<<endl;
	}
}

void timeNearestNeighbor(PointSplitNode<int, 2>* tree, list<Item<int, 2> > items, char* name)
{
	struct timeval start;
	gettimeofday(&start, 0);

	findNeighbors(tree, items);

	struct timeval end;
	gettimeofday(&end, 0);

	double elapsed = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec)/1e6;

	cerr<<"search with "<<name<<" took "<<elapsed<<" seconds."<<endl;
}

int main(int argc, char* argv[])
{
	if (argc == 0) {
		return 1;
	}

	list<Item<int, 2> > items = loadFile(argc, argv);
	PointSplitNodePrinter<int, 2> printer;
	SimpleTreeBuilder<int, 2> simple_builder;
	MidpointTreeBuilder<int, 2> midpoint_builder;

	PointSplitNode<int, 2>* simple_root = simple_builder.build(items);
	PointSplitNode<int, 2>* midpoint_root = midpoint_builder.build(items);

	timeNearestNeighbor(simple_root, items, "simple tree");
	timeNearestNeighbor(midpoint_root, items, "midpoint tree");

	return 0;
}
