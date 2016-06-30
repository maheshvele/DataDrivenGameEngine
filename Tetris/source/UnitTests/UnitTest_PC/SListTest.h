#include <cxxtest/TestSuite.h>
#include "SList.h"
#include "Foo.h"

using namespace Library;

class MyTestSuite : public CxxTest::TestSuite
{
public:

	void setUp(void)
	{
		//Confirm everything is empty
		TS_ASSERT(mIntList.IsEmpty());
		TS_ASSERT(mIntPointerList.IsEmpty());
		TS_ASSERT(mFooList.IsEmpty());


#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif
	}

	void tearDown(void)
	{
		//Clear things and confirm that they are empty
		mIntList.Clear();
		TS_ASSERT(mIntList.IsEmpty());

		mIntPointerList.Clear();
		TS_ASSERT(mIntPointerList.IsEmpty());

		mFooList.Clear();
		TS_ASSERT(mFooList.IsEmpty());

#ifdef _DEBUG
		//Compare the memory state at the end to our snapshot at the beginning
		_CrtMemState endSnapshpt, difference;
		_CrtMemCheckpoint(&endSnapshpt);
		if (_CrtMemDifference(&difference, &startSnapshot, &endSnapshpt))
		{
			_CrtMemDumpStatistics(&difference);
		}
#endif
	}

	void TestEmptyException(void)
	{
		mIntList.Clear();
		TS_ASSERT_THROWS_ANYTHING(mIntList.Front());
		TS_ASSERT_THROWS_ANYTHING(mIntList.Back());

		mIntPointerList.Clear();
		TS_ASSERT_THROWS_ANYTHING(mIntPointerList.Front());
		TS_ASSERT_THROWS_ANYTHING(mIntPointerList.Back());

		mFooList.Clear();
		TS_ASSERT_THROWS_ANYTHING(mFooList.Front());
		TS_ASSERT_THROWS_ANYTHING(mFooList.Back());
	}

	void TestPushFront(void)
	{
		int a = 1;
		int* aPointer = &a;
		Foo testFoo(a);

		mIntList.PushFront(1);
		TS_ASSERT_EQUALS(mIntList.Front(), a);

		mIntPointerList.PushFront(aPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), aPointer);

		mFooList.PushFront(testFoo);
		TS_ASSERT_EQUALS(mFooList.Front(), testFoo);

	}

	void TestPopFront(void)
	{
		int a = 1;
		int* aPointer = &a;
		Foo testFoo(a);

		mIntList.PushFront(a);
		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

		mIntPointerList.PushFront(aPointer);
		mIntPointerList.PopFront();
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);

		mFooList.PushFront(testFoo);
		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Size(), 0);
	}

	void TestPushBack(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo testFooA(a);
		Foo testFooB(b);

		mIntList.PushFront(a);
		mIntList.PushBack(b);
		TS_ASSERT_EQUALS(mIntList.Back(), b);

		mIntPointerList.PushFront(aPointer);
		mIntPointerList.PushBack(bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), bPointer);

		mFooList.PushFront(testFooA);
		mFooList.PushBack(testFooB);
		TS_ASSERT_EQUALS(mFooList.Back(), testFooB);
	}


	void TestCopy(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo testFooA(a);
		Foo testFooB(b);

		//Test int list
		mIntList.PushFront(a);
		mIntList.PushFront(b);
		SList<int> copyIntList(mIntList);

		TS_ASSERT_EQUALS(copyIntList.Size(), mIntList.Size());

		while (mIntList.Size() > 0)
		{
			TS_ASSERT_EQUALS(copyIntList.Front(), mIntList.Front());
			copyIntList.PopFront();
			mIntList.PopFront();
		}

		//Test pointer list
		mIntPointerList.PushFront(aPointer);
		mIntPointerList.PushBack(bPointer);
		SList<int*> copyPointerList(mIntPointerList);

		TS_ASSERT_EQUALS(copyPointerList.Size(), mIntPointerList.Size());

		while (mIntPointerList.Size() > 0)
		{
			TS_ASSERT_EQUALS(copyPointerList.Front(), mIntPointerList.Front());
			copyPointerList.PopFront();
			mIntPointerList.PopFront();
		}

		//Test foo list
		mFooList.PushFront(testFooA);
		mFooList.PushFront(testFooB);
		SList<Foo> copyFooList(mFooList);

		TS_ASSERT_EQUALS(copyFooList.Size(), mFooList.Size())
		
		while (mFooList.Size() > 0)
		{
			TS_ASSERT_EQUALS(copyFooList.Front(), mFooList.Front())
			copyFooList.PopFront();
			mFooList.PopFront();
		}

	}

	void TestOrder(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo testFooA(a);
		Foo testFooB(b);

		//Test int list
		//Verify PushFront inserts in the correct order
		mIntList.PushFront(a);
		mIntList.PushFront(b);
		TS_ASSERT_EQUALS(mIntList.Front(), b);
		TS_ASSERT_EQUALS(mIntList.Back(), a);
		mIntList.Clear();

		//Verify PushBack inserts in the correct order
		mIntList.PushBack(a);
		mIntList.PushBack(b);
		TS_ASSERT_EQUALS(mIntList.Front(), a);
		TS_ASSERT_EQUALS(mIntList.Back(), b);
		mIntList.Clear();

		//Verify PushFront and PushBack can be used together and result in a properly ordered list
		mIntList.PushBack(a);
		mIntList.PushFront(b);
		TS_ASSERT_EQUALS(mIntList.Front(), b);
		TS_ASSERT_EQUALS(mIntList.Back(), a);
		mIntList.Clear();

		//Test pointer list
		//Verify PushFront inserts in the correct order
		mIntPointerList.PushFront(aPointer);
		mIntPointerList.PushFront(bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), aPointer);
		mIntPointerList.Clear();

		//Verify PushBack inserts in the correct order
		mIntPointerList.PushBack(aPointer);
		mIntPointerList.PushBack(bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), aPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), bPointer);
		mIntPointerList.Clear();

		//Verify PushFront and PushBack can be used together and result in a properly ordered list
		mIntPointerList.PushBack(aPointer);
		mIntPointerList.PushFront(bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), aPointer);
		mIntPointerList.Clear();

		//Test foo list
		//Verify PushFront inserts in the correct order
		mFooList.PushFront(testFooA);
		mFooList.PushFront(testFooB);
		TS_ASSERT_EQUALS(mFooList.Front(), testFooB);
		TS_ASSERT_EQUALS(mFooList.Back(), testFooA);
		mFooList.Clear();

		//Verify PushBack inserts in the correct order
		mFooList.PushBack(testFooA);
		mFooList.PushBack(testFooB);
		TS_ASSERT_EQUALS(mFooList.Front(), testFooA);
		TS_ASSERT_EQUALS(mFooList.Back(), testFooB);
		mFooList.Clear();

		//Verify PushFront and PushBack can be used together and result in a properly ordered list
		mFooList.PushBack(testFooA);
		mFooList.PushFront(testFooB);
		TS_ASSERT_EQUALS(mFooList.Front(), testFooB);
		TS_ASSERT_EQUALS(mFooList.Back(), testFooA);
		mFooList.Clear();
	}

	void TestIteratorEquality(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo aFoo(a);
		Foo bFoo(b);
		mIntList.PushBack(a);
		mIntPointerList.PushBack(aPointer);
		mFooList.PushBack(aFoo);
		SList<int>::Iterator intIterator = mIntList.begin();
		SList<int>::Iterator otherIntIterator = mIntList.begin();
		SList<int*>::Iterator intPointerIterator = mIntPointerList.begin();
		SList<int*>::Iterator otherIntPointerIterator = mIntPointerList.begin();
		SList<Foo>::Iterator fooIterator = mFooList.begin();
		SList<Foo>::Iterator otherFooIterator = mFooList.begin();


		//Test case where the iterators are equal
		TS_ASSERT(intIterator == otherIntIterator);
		TS_ASSERT(!(intIterator != otherIntIterator));
		TS_ASSERT(intPointerIterator == otherIntPointerIterator);
		TS_ASSERT(!(intPointerIterator != otherIntPointerIterator));
		TS_ASSERT(fooIterator == otherFooIterator);
		TS_ASSERT(!(fooIterator != otherFooIterator));

		mIntList.PushFront(b);
		mIntPointerList.PushFront(bPointer);
		mFooList.PushFront(bFoo);
		otherIntIterator = mIntList.begin();
		otherIntPointerIterator = mIntPointerList.begin();
		otherFooIterator = mFooList.begin();

		//Test case where the iterators are not equal
		TS_ASSERT(intIterator != otherIntIterator);
		TS_ASSERT(!(intIterator == otherIntIterator));
		TS_ASSERT(intPointerIterator != otherIntPointerIterator);
		TS_ASSERT(!(intPointerIterator == otherIntPointerIterator));
		TS_ASSERT(fooIterator != otherFooIterator);
		TS_ASSERT(!(fooIterator == otherFooIterator));

		//Test equality operator with iterators for end()
		otherIntIterator = mIntList.end();
		TS_ASSERT(!(intIterator == otherIntIterator));
		TS_ASSERT(intIterator != otherIntIterator);
		intIterator = mIntList.end();
		TS_ASSERT(intIterator == otherIntIterator);
		TS_ASSERT(!(intIterator != otherIntIterator));
	}

	void TestIteratorIncrement(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo aFoo(a);
		Foo bFoo(b);

		mIntList.PushFront(a);
		SList<int>::Iterator intIterator = mIntList.begin();
		mIntList.PushFront(b);
		SList<int>::Iterator otherIntIterator = mIntList.begin();

		mIntPointerList.PushFront(aPointer);
		SList<int*>::Iterator intPointerIterator = mIntPointerList.begin();
		mIntPointerList.PushFront(bPointer);
		SList<int*>::Iterator otherIntPointerIterator = mIntPointerList.begin();

		mFooList.PushFront(aFoo);
		SList<Foo>::Iterator fooIterator = mFooList.begin();
		mFooList.PushFront(bFoo);
		SList<Foo>::Iterator otherFooIterator = mFooList.begin();

		//Test prefix
		++otherIntIterator;
		TS_ASSERT_EQUALS(intIterator, otherIntIterator);
		++otherIntPointerIterator;
		TS_ASSERT_EQUALS(intPointerIterator, otherIntPointerIterator);
		++otherFooIterator;
		TS_ASSERT_EQUALS(fooIterator, otherFooIterator);

		//Test postfix
		otherIntIterator = mIntList.begin();
		otherIntIterator++;
		otherIntPointerIterator = mIntPointerList.begin();
		otherIntPointerIterator++;
		otherFooIterator = mFooList.begin();
		otherFooIterator++;
		TS_ASSERT_EQUALS(intIterator, otherIntIterator);
		TS_ASSERT_EQUALS(intPointerIterator, otherIntPointerIterator);
		TS_ASSERT_EQUALS(fooIterator, otherFooIterator);

		//Test postfix return value
		otherIntIterator = mIntList.begin();
		intIterator = otherIntIterator++;
		otherIntPointerIterator = mIntPointerList.begin();
		intPointerIterator = otherIntPointerIterator++;
		otherFooIterator = mFooList.begin();
		fooIterator = otherFooIterator++;
		TS_ASSERT_DIFFERS(intIterator, otherIntIterator);
		TS_ASSERT_DIFFERS(intPointerIterator, otherIntPointerIterator);
		TS_ASSERT_DIFFERS(fooIterator, otherFooIterator);
	}

	void TestIteratorDereference(void)
	{
		int a = 1;
		int* aPointer = &a;
		Foo aFoo(a);
		mIntList.PushBack(a);
		mIntPointerList.PushBack(aPointer);
		mFooList.PushBack(aFoo);
		SList<int>::Iterator intIterator = mIntList.begin();
		SList<int*>::Iterator intPointerIterator = mIntPointerList.begin();
		SList<Foo>::Iterator fooIterator = mFooList.begin();
		TS_ASSERT_EQUALS(*intIterator, a);
		TS_ASSERT_EQUALS(*intPointerIterator, aPointer);
		TS_ASSERT_EQUALS(*fooIterator, aFoo);

		//Test exceptions for dereferencing the end
		TS_ASSERT_THROWS_ANYTHING(*(mIntList.end()));
		TS_ASSERT_THROWS_ANYTHING(*(mIntPointerList.end()));
		TS_ASSERT_THROWS_ANYTHING(*(mFooList.end()));
	}

	void TestInsertAfter(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;
		mIntList.PushBack(a);
		mIntList.PushBack(c);

		int* aPointer = &a;
		int* bPointer = &b;
		int* cPointer = &c;
		mIntPointerList.PushBack(aPointer);
		mIntPointerList.PushBack(cPointer);

		Foo aFoo(a);
		Foo bFoo(b);
		Foo cFoo(c);
		mFooList.PushBack(aFoo);
		mFooList.PushBack(cFoo);

		SList<int>::Iterator intIterator = mIntList.begin();
		SList<int>::Iterator otherIntIterator = mIntList.begin();

		SList<int*>::Iterator intPointerIterator = mIntPointerList.begin();
		SList<int*>::Iterator otherIntPointerIterator = mIntPointerList.begin();

		SList<Foo>::Iterator fooIterator = mFooList.begin();
		SList<Foo>::Iterator otherFooIterator = mFooList.begin();

		//Insert b after a. This places it between a and c
		mIntList.InsertAfter(b, intIterator);
		mIntPointerList.InsertAfter(bPointer, intPointerIterator);
		mFooList.InsertAfter(bFoo, fooIterator);

		++otherIntIterator;
		TS_ASSERT(*otherIntIterator == b);
		++otherIntIterator;
		TS_ASSERT(*otherIntIterator == c);


		++otherIntPointerIterator;
		TS_ASSERT(*otherIntPointerIterator == bPointer);
		++otherIntPointerIterator;
		TS_ASSERT(*otherIntPointerIterator == cPointer);

		++otherFooIterator;
		TS_ASSERT(*otherFooIterator == bFoo);
		++otherFooIterator;
		TS_ASSERT(*otherFooIterator == cFoo);
		mIntList.Clear();
	}

	void TestFind(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;
		mIntList.PushBack(a);
		mIntList.PushBack(b);
		mIntList.PushBack(c);
		int* aPointer = &a;
		int* bPointer = &b;
		int* cPointer = &c;
		mIntPointerList.PushBack(aPointer);
		mIntPointerList.PushBack(bPointer);
		mIntPointerList.PushBack(cPointer);
		Foo aFoo(a);
		Foo bFoo(b);
		Foo cFoo(c);
		mFooList.PushBack(aFoo);
		mFooList.PushBack(bFoo);
		mFooList.PushBack(cFoo);

		SList<int>::Iterator intIterator = mIntList.Find(b);
		TS_ASSERT(*intIterator == b);
		
		SList<int*>::Iterator intPointerIterator = mIntPointerList.Find(bPointer);
		TS_ASSERT(*intPointerIterator == bPointer);

		SList<Foo>::Iterator fooIterator = mFooList.Find(bFoo);
		TS_ASSERT(*fooIterator == bFoo);

		//Test for item not in list
		mIntList.PopFront();
		intIterator = mIntList.Find(a);
		TS_ASSERT(intIterator == mIntList.end());

		mIntPointerList.PopFront();
		intPointerIterator = mIntPointerList.Find(aPointer);
		TS_ASSERT(intPointerIterator == mIntPointerList.end());

		mFooList.PopFront();
		fooIterator = mFooList.Find(aFoo);
		TS_ASSERT(fooIterator == mFooList.end());
	}

	void TestRemove(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;
		mIntList.PushBack(a);
		mIntList.PushBack(b);
		mIntList.PushBack(c);
		int* aPointer = &a;
		int* bPointer = &b;
		int* cPointer = &c;
		mIntPointerList.PushBack(aPointer);
		mIntPointerList.PushBack(bPointer);
		mIntPointerList.PushBack(cPointer);
		Foo aFoo(a);
		Foo bFoo(b);
		Foo cFoo(c);
		mFooList.PushBack(aFoo);
		mFooList.PushBack(bFoo);
		mFooList.PushBack(cFoo);

		mIntList.Remove(b);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		TS_ASSERT_EQUALS(mIntList.Front(), a);
		TS_ASSERT_EQUALS(mIntList.Back(), c);

		mIntPointerList.Remove(aPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), bPointer);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), cPointer);

		mFooList.Remove(bFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);
		TS_ASSERT_EQUALS(mFooList.Front(), aFoo);
		TS_ASSERT_EQUALS(mFooList.Back(), cFoo);
	}

private:
	SList<int> mIntList;
	SList<int*> mIntPointerList;
	SList<Foo> mFooList; 
	_CrtMemState startSnapshot;
};