#include "KDTree.h"

#include <fstream>
#include <vector>

#include <Eigen/Core>

using Eigen::Vector2d;
using Eigen::Vector3d;
using std::ifstream;
using std::vector;

int main(int argc, char* argv[])
{
	vector<int> ids;

	int maxlines = 1000000;
	KDTree<int> tree;

	if (argc > 1) {
		ifstream file(argv[1]);
		if (file) {
			int maxlines = 1000000;
			if (argc > 2) {
				maxlines = atoi(argv[2]);
			}
			for (int i = 0; i < maxlines; i++) {
				int id;
				double x, y;
				file>>id>>x>>y;
				if (file.eof()) {
					break;
				}
				tree.insertPoint(Vector2d(x,y), id);
				ids.push_back(id);
			}
			tree.nearestNeighbor(Vector2d(.5,.1));
		}
	} else {
		//test 3d tree
		KDTree<int, 3> tree3d;
		tree3d.insertPoint(Vector3d(1,2,3),1);
		tree3d.insertPoint(Vector3d(2,3,4),1);
		tree3d.insertPoint(Vector3d(3,4,5),1);
		tree3d.print();
		tree3d.nearestNeighbor(Vector3d(3,3,3));
	}

	return 0;
}
