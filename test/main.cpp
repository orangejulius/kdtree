#include "test/KDTreeTest.h"
#include "test/KDNodePrinterTest.h"
#include "test/KDNodeTest.h"

int main() {
	Test::Suite ts;

	ts.add(std::auto_ptr<Test::Suite>(new KDTreeTest));
	ts.add(std::auto_ptr<Test::Suite>(new KDNodePrinterTest));
	ts.add(std::auto_ptr<Test::Suite>(new KDNodeTest));

	Test::TextOutput output(Test::TextOutput::Verbose);
	return ts.run(output);
}
