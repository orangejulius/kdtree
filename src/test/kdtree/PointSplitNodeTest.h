#include <cpptest.h>

#include "kdtree/PointSplitNode.h"

using Eigen::Vector2d;

namespace KDTree {
	class PointSplitNodeTest : public Test::Suite {
		public:
			PointSplitNodeTest() {
				TEST_ADD(PointSplitNodeTest::new_node_is_leaf);
			}

		private:
			void new_node_is_leaf() {
				PointSplitNode<int, 2> node(2, Vector2d(3, 5));
				TEST_ASSERT(node.isLeaf());
			}
	};
}
