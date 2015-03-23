#include <cpptest.h>

#include <Eigen/Geometry>

#include "kdtree/MidpointTreeBuilder.h"

using Eigen::Vector2d;

namespace KDTree {
	class MidpointTreeBuilderTest : public Test::Suite {
		public:
			MidpointTreeBuilderTest() {
				TEST_ADD(MidpointTreeBuilderTest::builder_sets_root_to_middle_of_three_elements);
			}
		private:
			void builder_sets_root_to_middle_of_three_elements() {
				MidpointTreeBuilder<int, 2> builder;
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(1, Vector2d(4, 7)));
				items.push_back(Item<int, 2>(2, Vector2d(5, 7)));
				items.push_back(Item<int, 2>(3, Vector2d(6, 7)));

				PointSplitNode<int, 2>* result = builder.build(items);

				TEST_ASSERT(result);
				if (result) {
					TEST_ASSERT(result->getPoint() == Vector2d(5, 7));
					TEST_ASSERT(result->getData() == 2);

					PointSplitNode<int, 2>* left = result->getLeft();
					TEST_ASSERT(left);
					if (left) {
						TEST_ASSERT(left->getData() == 1);
						TEST_ASSERT(left->getPoint() == Vector2d(4, 7));
						TEST_ASSERT(left->getLeft() == 0);
						TEST_ASSERT(left->getRight() == 0);
					}

					PointSplitNode<int, 2>* right = result->getRight();
					TEST_ASSERT(right);
					if (right) {
						TEST_ASSERT(right->getData() == 3);
						TEST_ASSERT(right->getPoint() == Vector2d(6, 7));
						TEST_ASSERT(right->getLeft() == 0);
						TEST_ASSERT(right->getRight() == 0);
					}
				}
			}
	};
}
