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
				TEST_ADD(SimpleTreeBuilderTest::builder_returns_tree_from_three_item_list);
				TEST_ADD(SimpleTreeBuilderTest::builder_alternates_comparison_axis_at_each_depth);
				TEST_ADD(SimpleTreeBuilderTest::plane_split_builder_returns_leaf_node_for_one_item_array);
				TEST_ADD(SimpleTreeBuilderTest::plane_split_builder_returns_tree_for_four_item_array);
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

			void builder_returns_tree_from_three_item_list() {
				SimpleTreeBuilder<int, 2> builder;
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(1, Vector2d(5, 7)));
				items.push_back(Item<int, 2>(2, Vector2d(4, 7)));
				items.push_back(Item<int, 2>(3, Vector2d(6, 7)));

				PointSplitNode<int, 2>* result = builder.build(items);

				TEST_ASSERT(result);
				if (result) {
					TEST_ASSERT(result->getPoint() == Vector2d(5, 7));
					TEST_ASSERT(result->getData() == 1);

					PointSplitNode<int, 2>* left = result->getLeft();
					TEST_ASSERT(left);
					if (left) {
						TEST_ASSERT(left->getData() == 2);
						TEST_ASSERT(left->getPoint() == Vector2d(4, 7));
						TEST_ASSERT(left->getLeft() == 0);
						TEST_ASSERT(left->getRight() == 0);
					}

					PointSplitNode<int, 2>* right = result->getRight();
					if (right) {
						TEST_ASSERT(right->getData() == 3);
						TEST_ASSERT(right->getPoint() == Vector2d(6, 7));
						TEST_ASSERT(right->getLeft() == 0);
						TEST_ASSERT(right->getRight() == 0);
					}
				}
			}

			void builder_alternates_comparison_axis_at_each_depth() {
				SimpleTreeBuilder<int, 2> builder;
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(1, Vector2d(4, 8)));
				items.push_back(Item<int, 2>(2, Vector2d(5, 8)));
				items.push_back(Item<int, 2>(3, Vector2d(6, 7)));

				PointSplitNode<int, 2>* result = builder.build(items);

				TEST_ASSERT(result);
				if (result) {
					TEST_ASSERT(result->getPoint() == Vector2d(4, 8));
					TEST_ASSERT(result->getData() == 1);
					TEST_ASSERT(result->getLeft() == 0);

					PointSplitNode<int, 2>* right = result->getRight();
					TEST_ASSERT(right);
					if (right) {
						TEST_ASSERT(right->getData() == 2);
						TEST_ASSERT(right->getPoint() == Vector2d(5, 8));
						TEST_ASSERT(right->getRight() == 0);

						PointSplitNode<int, 2>* left = right->getLeft();
						TEST_ASSERT(left);
						if (left) {
							TEST_ASSERT(left->getData() == 3);
							TEST_ASSERT(left->getPoint() == Vector2d(6, 7));
							TEST_ASSERT(left->getLeft() == 0);
							TEST_ASSERT(left->getRight() == 0);
						}
					}
				}
			}

			void plane_split_builder_returns_leaf_node_for_one_item_array() {
				SimpleTreeBuilder<int, 2> builder;
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(10, Vector2d(2, 3)));

				PlaneSplitNode<int, 2>* result = builder.build_plane_split(items, 5);
				TEST_ASSERT(result);
				if (result) {
					TEST_ASSERT(result->getPartition() == 0.0);
					TEST_ASSERT(result->getAxis() == 0);
					TEST_ASSERT(result->getItems() == items);
					TEST_ASSERT(result->getLeft() == 0);
					TEST_ASSERT(result->getRight() == 0);
				}
			}

			void plane_split_builder_returns_tree_for_four_item_array() {
				SimpleTreeBuilder<int, 2> builder;
				list<Item<int, 2> > items;
				items.push_back(Item<int, 2>(1, Vector2d(2, 3)));
				items.push_back(Item<int, 2>(2, Vector2d(3, 3)));
				items.push_back(Item<int, 2>(3, Vector2d(4, 3)));
				items.push_back(Item<int, 2>(4, Vector2d(1, 3)));
				PlaneSplitNode<int, 2>* result = builder.build_plane_split(items, 3);
				TEST_ASSERT(result);
				if (result) {
					TEST_ASSERT(result->getPartition() == 2.0);
					TEST_ASSERT(result->getAxis() == 0);
					TEST_ASSERT(result->getItems().size() == 0);
					TEST_ASSERT(result->getLeft());
					PlaneSplitNode<int, 2>* left = result->getLeft();
					if (left) {
						TEST_ASSERT(left->getItems().size() == 1);
						TEST_ASSERT(left->getItems().begin()->item == 4);
					}
					TEST_ASSERT(result->getRight());
					PlaneSplitNode<int, 2>* right = result->getRight();
					if (right) {
						list<Item<int, 2> > expectedRightItems;
						expectedRightItems.push_back(Item<int, 2>(1, Vector2d(2, 3)));
						expectedRightItems.push_back(Item<int, 2>(2, Vector2d(3, 3)));
						expectedRightItems.push_back(Item<int, 2>(3, Vector2d(4, 3)));
						TEST_ASSERT(right->getItems() == expectedRightItems);
					}
				}
			}

	};
}
