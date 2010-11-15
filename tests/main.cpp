#include "KDTree.h"

int main()
{
	KDTree<int> tree;
	tree.insertPoint(Vector2d(7,2), 1);
	tree.insertPoint(Vector2d(9,6), 2);
	tree.insertPoint(Vector2d(5,4), 3);
	tree.insertPoint(Vector2d(2,3), 4);
	tree.insertPoint(Vector2d(8,1), 5);
	tree.insertPoint(Vector2d(4,7), 6);
	tree.print();
	return 0;
}
