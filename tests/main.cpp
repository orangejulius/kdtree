#include "KDTree.h"

#include <fstream>
#include <vector>

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
	}

	return 0;
}
