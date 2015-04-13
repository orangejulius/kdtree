#include <cpptest.h>
#include <sstream>

#include "kdtree/Printer.h"

using Eigen::Vector2d;
using Eigen::Vector3d;

namespace KDTree {
	class PrinterTest : public Test::Suite {
		public:
			PrinterTest() {
				TEST_ADD(PrinterTest::single_node_prints_point_and_data);
				TEST_ADD(PrinterTest::node_prints_left_child_then_self);
				TEST_ADD(PrinterTest::node_prints_self_then_right_child);
				TEST_ADD(PrinterTest::single_internal_node_prints_axis_and_partition);
				TEST_ADD(PrinterTest::multiple_nodes_printed_inorder);
				TEST_ADD(PrinterTest::leaf_node_prints_points);
			}

		private:
			void single_node_prints_point_and_data() {
				PointSplitNode<int, 2> node(5, Vector2d(1, 2));
				Printer<int, 2> printer;
				std::ostringstream out;

				printer.print(&node, out);

				TEST_ASSERT(out.str() == "(1, 2) 5\n");
			};

			void node_prints_left_child_then_self() {
				PointSplitNode<int, 2> root(5, Vector2d(1, 2));
				PointSplitNode<int, 2> child(10, Vector2d(0, 9));
				Printer<int, 2> printer;
				std::ostringstream out;

				root.setLeft(&child);
				printer.print(&root, out);

				TEST_ASSERT(out.str() == "(0, 9) 10\n(1, 2) 5\n");
			}

			void node_prints_self_then_right_child() {
				PointSplitNode<int, 2> root(5, Vector2d(1, 2));
				PointSplitNode<int, 2> child(60, Vector2d(6, 3));
				Printer<int, 2> printer;
				std::ostringstream out;

				root.setRight(&child);
				printer.print(&root, out);

				TEST_ASSERT(out.str() == "(1, 2) 5\n(6, 3) 60\n");
			}

			void single_internal_node_prints_axis_and_partition() {
				PlaneSplitNode<int, 2> root(1, 2);
				Printer<int, 2> printer;
				std::ostringstream out;

				printer.print(&root, out);

				TEST_ASSERT(out.str() == "1 2\n");
			}

			void multiple_nodes_printed_inorder() {
				PlaneSplitNode<int, 2> left(2, 3);
				PlaneSplitNode<int, 2> root(1, 4, &left);
				Printer<int, 2> printer;
				std::ostringstream out;

				printer.print(&root, out);

				TEST_ASSERT(out.str() == "2 3\n1 4\n");
			}

			void leaf_node_prints_points() {
				list<Item<int, 3> > items;
				items.push_back(Item<int, 3>(1, Vector3d(2, 3, 4)));
				items.push_back(Item<int, 3>(5, Vector3d(6, 7, 8)));
				PlaneSplitNode<int, 3> node(items);
				Printer<int, 3> printer;
				std::ostringstream out;

				printer.print(&node, out);

				TEST_ASSERT(out.str() == "1 (2, 3, 4) 5 (6, 7, 8) \n");
			}
	};
}
