#include "KDTree.h"

#include <fstream>
#include <vector>

#include <Eigen/Core>

using Eigen::Vector2d;
using Eigen::Vector3d;
using std::ifstream;
using std::vector;

struct Item
{
	Vector2d point;
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
				item.point = Vector2d(x,y);
				if (file.eof()) {
					break;
				}
				tree.insertPoint(item.point, item.id);
				items.push_back(item);
			}
			tree.nearestNeighbor(Vector2d(.5,.1));
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
	} else {
		//test 3d tree
		KDTree<int, 3> tree3d;
		tree3d.insertPoint(Vector3d(2,2,3),1);
		tree3d.insertPoint(Vector3d(2,3,4),1);
		tree3d.insertPoint(Vector3d(3,4,5),1);
		tree3d.print();
		tree3d.nearestNeighbor(Vector3d(3,3,3),3);

		list<KDNode<int, 3>* > neighborList = tree3d.nearestNeighbor(Vector3d(3,3,3),3);
		list<KDNode<int, 3>* >::iterator it;
		cout<<"Size of list: "<<neighborList.size()<<endl;
		for (it = neighborList.begin(); it != neighborList.end(); it++) {
			cout<<(*it)->getPoint()<<endl;
		}
	}

	return 0;
}
