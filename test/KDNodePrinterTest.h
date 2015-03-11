#include <cpptest.h>
#include <sstream>

#include "KDNodePrinter.h"

class KDNodePrinterTest : public Test::Suite {
	public:
		KDNodePrinterTest() {
			TEST_ADD(KDNodePrinterTest::single_node_prints_point_and_data);
			TEST_ADD(KDNodePrinterTest::node_prints_left_child_then_self);
			TEST_ADD(KDNodePrinterTest::node_prints_self_then_right_child);
		}

	private:
		void single_node_prints_point_and_data() {
			KDNode<int, 2> node(5, Vector2d(1, 2));
			KDNodePrinter<int, 2> printer;
			std::ostringstream out;

			printer.print(node, out);

			TEST_ASSERT(out.str() == "(1, 2) 5\n");
		};

		void node_prints_left_child_then_self() {
			KDNode<int, 2> root(5, Vector2d(1, 2));
			KDNode<int, 2> child(10, Vector2d(0, 9));
			KDNodePrinter<int, 2> printer;
			std::ostringstream out;

			root.setLeft(&child);
			printer.print(root, out);

			TEST_ASSERT(out.str() == "(0, 9) 10\n(1, 2) 5\n");
		}

		void node_prints_self_then_right_child() {
			KDNode<int, 2> root(5, Vector2d(1, 2));
			KDNode<int, 2> child(60, Vector2d(6, 3));
			KDNodePrinter<int, 2> printer;
			std::ostringstream out;

			root.setRight(&child);
			printer.print(root, out);

			TEST_ASSERT(out.str() == "(1, 2) 5\n(6, 3) 60\n");
		}
};
