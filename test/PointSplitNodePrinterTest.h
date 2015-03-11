#include <cpptest.h>
#include <sstream>

#include "PointSplitNodePrinter.h"

using Eigen::Vector2d;

namespace KDTree {
	class PointSplitNodePrinterTest : public Test::Suite {
		public:
			PointSplitNodePrinterTest() {
				TEST_ADD(PointSplitNodePrinterTest::single_node_prints_point_and_data);
				TEST_ADD(PointSplitNodePrinterTest::node_prints_left_child_then_self);
				TEST_ADD(PointSplitNodePrinterTest::node_prints_self_then_right_child);
			}

		private:
			void single_node_prints_point_and_data() {
				PointSplitNode<int, 2> node(5, Vector2d(1, 2));
				PointSplitNodePrinter<int, 2> printer;
				std::ostringstream out;

				printer.print(&node, out);

				TEST_ASSERT(out.str() == "(1, 2) 5\n");
			};

			void node_prints_left_child_then_self() {
				PointSplitNode<int, 2> root(5, Vector2d(1, 2));
				PointSplitNode<int, 2> child(10, Vector2d(0, 9));
				PointSplitNodePrinter<int, 2> printer;
				std::ostringstream out;

				root.setLeft(&child);
				printer.print(&root, out);

				TEST_ASSERT(out.str() == "(0, 9) 10\n(1, 2) 5\n");
			}

			void node_prints_self_then_right_child() {
				PointSplitNode<int, 2> root(5, Vector2d(1, 2));
				PointSplitNode<int, 2> child(60, Vector2d(6, 3));
				PointSplitNodePrinter<int, 2> printer;
				std::ostringstream out;

				root.setRight(&child);
				printer.print(&root, out);

				TEST_ASSERT(out.str() == "(1, 2) 5\n(6, 3) 60\n");
			}
	};
}
