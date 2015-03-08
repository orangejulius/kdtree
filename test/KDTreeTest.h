#include <cpptest.h>

#include "KDTree.h"

class KDTreeTest : public Test::Suite {
	public:
	KDTreeTest() {
		TEST_ADD(KDTreeTest::depth_initialized_to_zero);
	}

	private:
	void depth_initialized_to_zero() {
		KDTree<int, 2> tree;
		TEST_ASSERT(tree.getMaxDepth() == 0);
	}
};
