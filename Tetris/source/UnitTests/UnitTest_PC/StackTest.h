#include <cxxtest/TestSuite.h>
#include "Stack.h"
#include "Foo.h"

using namespace Library;

class StackTestSuite : public CxxTest::TestSuite
{
public:
	void setUp(void)
	{		
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

	}

	void tearDown(void)
	{
		mIntStack.Clear();
		mPointerStack.Clear();
		mFooStack.Clear();
	}

	void TestPushTop(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo aFoo(a);
		Foo bFoo(b);

		mIntStack.Push(a);
		mIntStack.Push(b);
		mPointerStack.Push(aPointer);
		mPointerStack.Push(bPointer);
		mFooStack.Push(aFoo);
		mFooStack.Push(bFoo);

		TS_ASSERT_EQUALS(b, mIntStack.Top());
		TS_ASSERT_EQUALS(bPointer, mPointerStack.Top());
		TS_ASSERT_EQUALS(bFoo, mFooStack.Top());
	}

	void TestPop(void)
	{
		int a = 1;
		int* aPointer = &a;
		Foo aFoo(a);

		mIntStack.Push(a);
		mPointerStack.Push(aPointer);
		mFooStack.Push(aFoo);

		TS_ASSERT_EQUALS(mIntStack.Size(), 1);
		TS_ASSERT_EQUALS(mPointerStack.Size(), 1);
		TS_ASSERT_EQUALS(mFooStack.Size(), 1);

		mIntStack.Pop();
		mPointerStack.Pop();
		mFooStack.Pop();

		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		mIntStack.Push(a);

		//Test const version of pop and copy constructor 
		const Stack<int> constStack(mIntStack);
		TS_ASSERT_EQUALS(constStack.Top(), a);

	}

	void TestAssign(void)
	{
		int a = 1;
		int* aPointer = &a;
		Foo aFoo(a);

		mIntStack.Push(a);
		mPointerStack.Push(aPointer);
		mFooStack.Push(aFoo);

		Stack<int> mCopyIntStack = mIntStack;
		Stack<int*> mCopyPointerStack = mPointerStack;
		Stack<Foo> mCopyFooStack = mFooStack;
		
		TS_ASSERT_EQUALS(mCopyIntStack.Size(), mIntStack.Size());
		TS_ASSERT_EQUALS(mCopyPointerStack.Size(), mPointerStack.Size());
		TS_ASSERT_EQUALS(mCopyFooStack.Size(), mFooStack.Size());
		
		TS_ASSERT_EQUALS(mCopyIntStack.Top(), mIntStack.Top());
		TS_ASSERT_EQUALS(mCopyPointerStack.Top(), mPointerStack.Top());
		TS_ASSERT_EQUALS(mCopyFooStack.Top(), mFooStack.Top());		
	}


	
private:
	Stack<int> mIntStack;
	Stack<int*> mPointerStack;
	Stack<Foo> mFooStack;
};