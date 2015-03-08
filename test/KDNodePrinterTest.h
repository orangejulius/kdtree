#include <cpptest.h>
#include <sstream>

#include "KDNodePrinter.h"

class KDNodePrinterTest : public Test::Suite {
	public:
		KDNodePrinterTest() {
			TEST_ADD(KDNodePrinterTest::single_node_prints_point_and_data);
		}

	private:
		void single_node_prints_point_and_data() {
			KDNode<int, 2> node(5, Vector2d(1, 2));
			KDNodePrinter<int, 2> printer;

			std::ostringstream out;

			printer.print(node, out);

			TEST_ASSERT(out.str() == "1\n2\n5\n");
		};

};
