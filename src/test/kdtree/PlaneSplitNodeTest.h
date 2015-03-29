#include <cpptest.h>

#include "kdtree/PlaneSplitNode.h"

using Eigen::Vector2d;

namespace KDTree {
	class PlaneSplitNodeTest: public Test::Suite {
		public:
			PlaneSplitNodeTest() {
				TEST_ADD(PlaneSplitNodeTest::new_node_is_leaf);
				TEST_ADD(PlaneSplitNodeTest::new_node_with_items_is_leaf);
				TEST_ADD(PlaneSplitNodeTest::new_node_with_children_is_not_leaf);
			}
		private:
			void new_node_is_leaf() {
				PlaneSplitNode<int, 2> node(0, 0);

				TEST_ASSERT(node.isLeaf());
			}

			void new_node_with_items_is_leaf() {
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(1, Vector2d(2, 3)));

				PlaneSplitNode<int, 2> node(items);

				TEST_ASSERT(node.isLeaf());
			}
			void new_node_with_children_is_not_leaf() {
				PlaneSplitNode<int, 2> left(0, 0);
				PlaneSplitNode<int, 2> right(0, 0);
				PlaneSplitNode<int, 2> node(1, 2, &left, &right);

				TEST_ASSERT(!node.isLeaf());
				TEST_ASSERT(node.getLeft() == &left);
				TEST_ASSERT(node.getRight() == &right);
			}
	};
}
