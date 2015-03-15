#include "test/kdtree/NearestNeighborSearchTest.h"
#include "test/kdtree/NeighborListTest.h"
#include "test/kdtree/PointSplitNodeTest.h"
#include "test/kdtree/PointSplitNodePrinterTest.h"

using namespace KDTree;

int main() {
	Test::Suite ts;

	ts.add(std::auto_ptr<Test::Suite>(new NearestNeighborSearchTest));
	ts.add(std::auto_ptr<Test::Suite>(new NeighborListTest));
	ts.add(std::auto_ptr<Test::Suite>(new PointSplitNodePrinterTest));
	ts.add(std::auto_ptr<Test::Suite>(new PointSplitNodeTest));

	Test::TextOutput output(Test::TextOutput::Verbose);
	return ts.run(output);
}