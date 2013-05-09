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
	//test 3d tree
	KDTree<int, 3> tree3d;
	tree3d.insertPoint(Vector3d(2,2,3),1);
	tree3d.insertPoint(Vector3d(2,3,4),1);
	tree3d.insertPoint(Vector3d(3,4,5),1);
	tree3d.print();
	tree3d.nearestNeighbor(Vector3d(3,3,3),3);

	list<KDNode<int, 3>* > neighborList = tree3d.nearestNeighbor(Vector3d(3,3,3),3);
	list<KDNode<int, 3>* >::iterator it;
	assert(neighborList.size() == 3);
	for (it = neighborList.begin(); it != neighborList.end(); it++) {
		cout<<(*it)->getPoint()<<endl;
	}
}
