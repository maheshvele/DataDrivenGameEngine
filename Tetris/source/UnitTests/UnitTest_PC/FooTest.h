#include <cxxtest/TestSuite.h>
#include "Foo.h"

using namespace Library;

class FooTestSuite : public CxxTest::TestSuite
{
public:
	void TestFooInstantiation(void)
	{
		Foo* foo = nullptr;

		foo = new Foo();

		TS_ASSERT_DIFFERS(foo, nullptr);

		delete foo;
	}
};