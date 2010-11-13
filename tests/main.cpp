#include "KDTree.h"

int main()
{
	KDTree tree;
	tree.insertPoint(Vector2d(7,2));
	tree.insertPoint(Vector2d(9,6));
	tree.insertPoint(Vector2d(5,4));
	tree.insertPoint(Vector2d(2,3));
	tree.insertPoint(Vector2d(8,1));
	tree.insertPoint(Vector2d(4,7));
	tree.print();
	return 0;
}
