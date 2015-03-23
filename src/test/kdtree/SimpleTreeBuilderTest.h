#include <cpptest.h>

#include <Eigen/Geometry>

#include "kdtree/SimpleTreeBuilder.h"

using Eigen::Vector2d;

namespace KDTree {
	class SimpleTreeBuilderTest : public Test::Suite {
		public:
			SimpleTreeBuilderTest() {
				TEST_ADD(SimpleTreeBuilderTest::builder_returns_null_pointer_from_empty_list);
				TEST_ADD(SimpleTreeBuilderTest::builder_returns_single_node_from_one_item_list);
			}

		private:
			void builder_returns_null_pointer_from_empty_list() {
				SimpleTreeBuilder<int, 2> builder;
				list<Item<int, 2> > empty_list;
				PointSplitNode<int, 2>* result = builder.build(empty_list);

				TEST_ASSERT(result == 0);
			}

			void builder_returns_single_node_from_one_item_list() {
				SimpleTreeBuilder<int, 2> builder;
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(10, Vector2d(2, 3)));

				PointSplitNode<int, 2>* result = builder.build(items);

				TEST_ASSERT(result);
				if (result) {
					TEST_ASSERT(result->getPoint() == Vector2d(2,3));
					TEST_ASSERT(result->getData() == 10);
					TEST_ASSERT(result->getLeft() == 0);
					TEST_ASSERT(result->getRight() == 0);
				}
			}
	};
}
