#include "test/KDTreeTest.h"

int main() {
	Test::Suite ts;

	ts.add(std::auto_ptr<Test::Suite>(new KDTreeTest));

	Test::TextOutput output(Test::TextOutput::Terse);
	return ts.run(output);
}
