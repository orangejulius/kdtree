#include "KDNode.h"

using std::cout;
using std::endl;

KDNode::KDNode(Vector2d point, unsigned depth, unsigned numAxes, KDNode* parent): point(point), depth(depth), numAxes(numAxes), parent(parent)
{
	left = 0;
	right = 0;
}

KDNode* KDNode::insertPoint(Vector2d newPoint)
{
	//the axis by which points will be compared
	int axis = depth % numAxes;
	if (newPoint[axis] > point[axis]) {
		//point goes to right node
		if (right) {
			return right->insertPoint(newPoint);
		} else {
			right = new KDNode(newPoint, depth + 1, numAxes, this);
			return right;
		}
	} else {
		//point goes to left node
		if (left) {
			return left->insertPoint(newPoint);
		} else {
			left = new KDNode(newPoint, depth + 1, numAxes, this);
			return left;
		}
	}
}

void KDNode::print(bool recursive) const
{
	if (recursive && left) left->print();
	cout << "Point: "<<point[0]<<","<<point[1]<<" Depth: "<<depth<<endl;
	if (recursive && right) right->print();
}
