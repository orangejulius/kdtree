#include <cpptest.h>

#include "KDNode.h"

class KDNodeTest : public Test::Suite {
	public:
		KDNodeTest() {
			TEST_ADD(KDNodeTest::new_node_is_leaf);
		}

	private:
		void new_node_is_leaf() {
			KDNode<int, 2> node(2, Vector2d(3, 5));
			TEST_ASSERT(node.isLeaf());
		}
};
