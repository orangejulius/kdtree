#include <cpptest.h>

#include "KDTree.h"

class KDTreeTest : public Test::Suite {
	public:
	KDTreeTest() {
		TEST_ADD(KDTreeTest::depth_initialized_to_zero);
		TEST_ADD(KDTreeTest::insert_increases_depth);
	}

	private:
	void depth_initialized_to_zero() {
		KDTree<int, 2> tree;
		TEST_ASSERT(tree.getMaxDepth() == 0);
	}

	void insert_increases_depth() {
		KDTree<int, 2> tree;

		tree.insertPoint(Vector2d(0, 0), 1);

		TEST_ASSERT(tree.getMaxDepth() == 1);
	}
};
