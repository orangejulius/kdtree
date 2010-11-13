#include "KDTree.h"

#include <iostream>

#include "KDNode.h"

using std::cout;
using std::endl;

KDTree::KDTree()
{
	root = 0;
	numNodes = 0;
	maxDepth = 0;
	numAxes = 2;//for now this only handles the 2D tree case
}

void KDTree::insertPoint(Vector2d newPoint)
{
	//if the tree already has an element in it, just add the point
	if (root) {
		KDNode* newnode = root->insertPoint(newPoint);

		//keep track of the max depth
		if (newnode->getDepth() > maxDepth) {
			maxDepth = newnode->getDepth();
		}
	} else {
		//otherwise create the root node of the tree
		root = new KDNode(newPoint, 0, numAxes, 0);
	}
	//keep track of the number of nodes inserted
	numNodes++;
}

void KDTree::print() const
{
	if (root) {
		root->print();
		cout << "Total nodes: "<<numNodes<<endl;
		cout << "Max depth: " << maxDepth << endl;
	} else {
		cout << "Tree is empty\n";
	}
}
