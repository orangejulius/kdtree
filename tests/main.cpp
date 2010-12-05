#include "KDTree.h"

#include <cstdlib>
#include <fstream>
#include <vector>

using std::ifstream;
using std::vector;

struct Item
{
	Point point;
	int id;
};

int main(int argc, char* argv[])
{
	vector<Item> items;

	int maxlines = 1000000;
	KDTree<int> tree;

	if (argc > 1) {
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
				Item item;
				item.id = id;
				item.point = Point(x,y);
				if (file.eof()) {
					break;
				}
				tree.insertPoint(item.point, item.id);
				items.push_back(item);
			}
			tree.nearestNeighbor(Point(.5,.1));
		}

		vector<Item>::iterator itemIt;
		for (itemIt = items.begin(); itemIt != items.end(); itemIt++) {
			cout<<(*itemIt).id<<" ";
			list <KDNode<int, 2>* > neighbors = tree.nearestNeighbor((*itemIt).point,4);
			list <KDNode<int, 2>* >::iterator it = neighbors.begin();
			//skip the first nearest neighbor (it is this point!)
			for (it++; it != neighbors.end(); it++) {
				cout<<(*it)->getData();
				if (it != --neighbors.end()) {
					cout<<",";
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
