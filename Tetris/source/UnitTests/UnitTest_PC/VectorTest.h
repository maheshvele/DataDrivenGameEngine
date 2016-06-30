#include <cxxtest/TestSuite.h>
#include "Vector.h"
#include "Foo.h"

using namespace Library;

class VectorTestSuite : public CxxTest::TestSuite
{
public:
	
	void setUp(void)
	{
		TS_ASSERT(mIntVector.IsEmpty());
		TS_ASSERT(mPointerVector.IsEmpty());
		TS_ASSERT(mFooVector.IsEmpty());
	}

	void tearDown(void)
	{		
		mIntVector.Clear();	
		mPointerVector.Clear();
		mFooVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());
		TS_ASSERT(mPointerVector.IsEmpty());
		TS_ASSERT(mFooVector.IsEmpty());
	}

	//Test front and back
	void TestFrontAndBack()
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo1(a);
		Foo myFoo2(b);

		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		TS_ASSERT_EQUALS(1, mIntVector.Front());
		TS_ASSERT_EQUALS(2, mIntVector.Back());

		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		TS_ASSERT_EQUALS(aPointer, mPointerVector.Front());
		TS_ASSERT_EQUALS(bPointer, mPointerVector.Back());

		mFooVector.PushBack(myFoo1);
		mFooVector.PushBack(myFoo2);
		TS_ASSERT_EQUALS(myFoo1, mFooVector.Front());
		TS_ASSERT_EQUALS(myFoo2, mFooVector.Back());
	}

	//Test push. Also handles testing reserve
	void TestPush(void)
	{		

		int a = 1;
		int b = 2;
		int c = 3;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo1(a);
		Foo myFoo2(b);

		//Test PushBack, Front, and Back
		//Since the vector should be empty right now, Reserve(2) is called here
		mIntVector.PushBack(a);
		
		int myInt = mIntVector.Front();
		int myInt2 = mIntVector.Back();
		TS_ASSERT_EQUALS(myInt, myInt2);
		mIntVector.PushBack(b);
		myInt2 = mIntVector.Back();
		TS_ASSERT_DIFFERS(myInt, myInt2);

		//Extra space is getting allocated if we try to push over capacity
		mIntVector.PushBack(c);
		myInt = mIntVector.Front();
		myInt2 = mIntVector.Back();
		TS_ASSERT_EQUALS(myInt, 1);
		TS_ASSERT_EQUALS(myInt2, 3);

		//Confirm that we can't reserve less space than we have
		TS_ASSERT_THROWS_ANYTHING(mIntVector.Reserve(1));

		//Test pointers
		mPointerVector.PushBack(aPointer);
		TS_ASSERT_EQUALS(mPointerVector.Front(), mPointerVector.Back());
		mPointerVector.PushBack(bPointer);
		TS_ASSERT_DIFFERS(mPointerVector.Front(), mPointerVector.Back());

		//Test foos
		mFooVector.PushBack(myFoo1);
		TS_ASSERT_EQUALS(mFooVector.Front(), mFooVector.Back());
		mFooVector.PushBack(myFoo2);
		TS_ASSERT_DIFFERS(mFooVector.Front(), mFooVector.Back());
	}

	void TestPop(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo1(a);
		Foo myFoo2(b);

		//Test ints
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		TS_ASSERT_EQUALS(2, mIntVector.Back());

		mIntVector.PopBack();
		TS_ASSERT_EQUALS(1, mIntVector.Back());

		//Test pointers
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		TS_ASSERT_EQUALS(bPointer, mPointerVector.Back());

		mPointerVector.PopBack();
		TS_ASSERT_EQUALS(aPointer, mPointerVector.Back());

		//Test foos
		mFooVector.PushBack(myFoo1);
		mFooVector.PushBack(myFoo2);
		TS_ASSERT_EQUALS(myFoo2, mFooVector.Back());

		mFooVector.PopBack();
		TS_ASSERT_EQUALS(myFoo1, mFooVector.Back());
	}

	void TestOperatorBrackets(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;
		int* aPointer = &a;
		int* bPointer = &b;
		int* cPointer = &c;
		Foo myFoo1(a);
		Foo myFoo2(b);
		Foo myFoo3(c);

		//Test ints
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mIntVector.PushBack(c);
		TS_ASSERT_EQUALS(mIntVector[0], 1);
		TS_ASSERT_EQUALS(mIntVector[1], 2);
		TS_ASSERT_EQUALS(mIntVector[2], 3);
		TS_ASSERT_THROWS_ANYTHING(mIntVector[999]);

		//Test pointers
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mPointerVector.PushBack(cPointer);
		TS_ASSERT_EQUALS(mPointerVector[0], aPointer);
		TS_ASSERT_EQUALS(mPointerVector[1], bPointer);
		TS_ASSERT_EQUALS(mPointerVector[2], cPointer);
		TS_ASSERT_THROWS_ANYTHING(mPointerVector[999]);

		//Test foos
		mFooVector.PushBack(myFoo1);
		mFooVector.PushBack(myFoo2);
		mFooVector.PushBack(myFoo3);
		TS_ASSERT_EQUALS(mFooVector[0], myFoo1);
		TS_ASSERT_EQUALS(mFooVector[1], myFoo2);
		TS_ASSERT_EQUALS(mFooVector[2], myFoo3);
		TS_ASSERT_THROWS_ANYTHING(mFooVector[999]);

		//Test const version
		const Vector<int> constVector = mIntVector;
		const int d = constVector.Front();
		const int e = constVector[1];
		const int f = constVector.Back();
		TS_ASSERT_EQUALS(d, 1);
		TS_ASSERT_EQUALS(e, 2);
		TS_ASSERT_EQUALS(f, 3);

	}

	void TestAt(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo1(a);
		Foo myFoo2(b);

		//Test ints
		mIntVector.Reserve(4);
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		TS_ASSERT_EQUALS(mIntVector.At(0), 1);
		TS_ASSERT_EQUALS(mIntVector.At(1), 2);

		//Test pointers
		mPointerVector.Reserve(4);
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		TS_ASSERT_EQUALS(mPointerVector.At(0), aPointer);
		TS_ASSERT_EQUALS(mPointerVector.At(1), bPointer);

		//Tes foos
		mFooVector.Reserve(4);
		mFooVector.PushBack(myFoo1);
		mFooVector.PushBack(myFoo2);
		TS_ASSERT_EQUALS(mFooVector.At(0), myFoo1);
		TS_ASSERT_EQUALS(mFooVector.At(1), myFoo2);

		//Ensure that exception is thrown when we go over capacity
		TS_ASSERT_THROWS_ANYTHING(mIntVector.At(99));

		//Ensure that size increases to accomidate at calls that go over size but under capacity
		int myInt = mIntVector.At(3);
		TS_ASSERT_EQUALS(mIntVector.Back(), myInt);
		TS_ASSERT_EQUALS(mIntVector.Size(), 4);
	}

	void TestCopy(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo1(a);
		Foo myFoo2(b);

		//Test ints
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);

		Vector<int> copyVector(mIntVector);

		TS_ASSERT_EQUALS(copyVector.Front(), mIntVector.Front());
		TS_ASSERT_EQUALS(copyVector.Back(), mIntVector.Back());
		TS_ASSERT_EQUALS(copyVector.Size(), mIntVector.Size());

		copyVector.Clear();
		copyVector = mIntVector;
		TS_ASSERT_EQUALS(copyVector.Front(), mIntVector.Front());
		TS_ASSERT_EQUALS(copyVector.Back(), mIntVector.Back());
		TS_ASSERT_EQUALS(copyVector.Size(), mIntVector.Size());

		//Test pointers
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);

		Vector<int*> copyPointerVector(mPointerVector);
		TS_ASSERT_EQUALS(copyPointerVector.Front(), mPointerVector.Front());
		TS_ASSERT_EQUALS(copyPointerVector.Back(), mPointerVector.Back());
		TS_ASSERT_EQUALS(copyPointerVector.Size(), mPointerVector.Size());

		copyPointerVector.Clear();
		copyPointerVector = mPointerVector;
		TS_ASSERT_EQUALS(copyPointerVector.Front(), mPointerVector.Front());
		TS_ASSERT_EQUALS(copyPointerVector.Back(), mPointerVector.Back());
		TS_ASSERT_EQUALS(copyPointerVector.Size(), mPointerVector.Size());

		//Test foos
		mFooVector.PushBack(myFoo1);
		mFooVector.PushBack(myFoo2);

		Vector<Foo> copyFooVector(mFooVector);
		TS_ASSERT_EQUALS(copyFooVector.Front(), mFooVector.Front());
		TS_ASSERT_EQUALS(copyFooVector.Back(), mFooVector.Back());
		TS_ASSERT_EQUALS(copyFooVector.Size(), mFooVector.Size());

		copyFooVector.Clear();
		copyFooVector = mFooVector;
		TS_ASSERT_EQUALS(copyFooVector.Front(), mFooVector.Front());
		TS_ASSERT_EQUALS(copyFooVector.Back(), mFooVector.Back());
		TS_ASSERT_EQUALS(copyFooVector.Size(), mFooVector.Size());
	}

	void TestIteratorAssign(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo1(a);
		Foo myFoo2(b);

		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mFooVector.PushBack(myFoo1);
		mFooVector.PushBack(myFoo2);

		Vector<int>::Iterator myIterator(0, &mIntVector);
		Vector<int*>::Iterator myPointerIterator(0, &mPointerVector);
		Vector<Foo>::Iterator myFooIterator(0, &mFooVector);

		//Test assignment and copy constructor
		//Test int
		Vector<int>::Iterator copyIterator(myIterator);
		TS_ASSERT(myIterator == copyIterator);
		copyIterator = myIterator;
		TS_ASSERT(myIterator == copyIterator);

		//Test pointer
		Vector<int*>::Iterator copyPointerIterator(myPointerIterator);
		TS_ASSERT(myPointerIterator == copyPointerIterator);
		copyPointerIterator = myPointerIterator;
		TS_ASSERT(myPointerIterator == copyPointerIterator);

		//Test foo
		Vector<Foo>::Iterator copyFooIterator(myFooIterator);
		TS_ASSERT(myFooIterator == copyFooIterator);
		copyFooIterator = myFooIterator;
		TS_ASSERT(myFooIterator == copyFooIterator);
	}

	void TestIteratorEquality(void)
	{
		int a = 1;
		int b = 2;

		mIntVector.PushBack(a);
		mIntVector.PushBack(b);

		Vector<int>::Iterator myIterator(0, &mIntVector);
		Vector<int*>::Iterator myIterator2(0, &mPointerVector);
		Vector<Foo>::Iterator myIterator3(0, &mFooVector);

		//Test equal operator
		TS_ASSERT(mIntVector.begin() == myIterator);
		TS_ASSERT(mPointerVector.begin() == myIterator2);
		TS_ASSERT(mFooVector.begin() == myIterator3);

		//Test for not-equal operator
		TS_ASSERT(mIntVector.end() != myIterator);		
	}

	void TestIteratorDereference(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo(a);
		Foo myFoo2(b);

		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mFooVector.PushBack(myFoo);
		mFooVector.PushBack(myFoo2);

		Vector<int>::Iterator myIterator(0, &mIntVector);
		Vector<int*>::Iterator myPointerIterator(0, &mPointerVector);
		Vector<Foo>::Iterator myFooIterator(0, &mFooVector);

		//Test dereference
		TS_ASSERT_EQUALS(*myIterator, 1);		
		TS_ASSERT_EQUALS(*myPointerIterator, aPointer);
		TS_ASSERT_EQUALS(*myFooIterator, myFoo);
	}

	void TestIteratorIncrement(void)
	{
		//Int
		int a = 1;
		int b = 2;

		mIntVector.PushBack(a);
		mIntVector.PushBack(b);

		Vector<int>::Iterator myIterator(0, &mIntVector);
		Vector<int>::Iterator copyIterator(myIterator);
		Vector<int>::Iterator backIterator(mIntVector.Size() - 1, &mIntVector);

		//Test prefix increment
		++myIterator;
		TS_ASSERT(myIterator == backIterator);

		//Test postfix increment
		TS_ASSERT(copyIterator++ != backIterator);
		TS_ASSERT(copyIterator == backIterator);

		//Pointer
		int* aPointer = &a;
		int* bPointer = &b;
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);

		Vector<int*>::Iterator myPointerIterator(0, &mPointerVector);
		Vector<int*>::Iterator copyPointerIterator(myPointerIterator);
		Vector<int*>::Iterator backPointerIterator(mPointerVector.Size() - 1, &mPointerVector);


		//Foo
		Foo myFoo(a);
		Foo myFoo2(b);
		mFooVector.PushBack(myFoo);
		mFooVector.PushBack(myFoo2);

		Vector<Foo>::Iterator myFooIterator(0, &mFooVector);
		Vector<Foo>::Iterator copyFooIterator(myFooIterator);
		Vector<Foo>::Iterator backFooIterator(mFooVector.Size() - 1, &mFooVector);

	}

	void TestIteratorBeginAndEnd(void)
	{
		int a = 1;
		int b = 2;
		int* aPointer = &a;
		int* bPointer = &b;
		Foo myFoo(a);
		Foo myFoo2(b);

		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mFooVector.PushBack(myFoo);
		mFooVector.PushBack(myFoo2);

		//Test int
		Vector<int>::Iterator frontIterator(0, &mIntVector);
		TS_ASSERT(frontIterator == mIntVector.begin());
		TS_ASSERT(frontIterator != mIntVector.end());

		//Test pointer
		Vector<int*>::Iterator frontPointerIterator(0, &mPointerVector);
		TS_ASSERT(frontPointerIterator == mPointerVector.begin());
		TS_ASSERT(frontPointerIterator != mPointerVector.end());

		//Test foo
		Vector<Foo>::Iterator frontFooIterator(0, &mFooVector);
		TS_ASSERT(frontFooIterator == mFooVector.begin());
		TS_ASSERT(frontFooIterator != mFooVector.end());
	}

	void TestIteratorFind(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;
		int d = 4;
		int* aPointer = &a;
		int* bPointer = &b;
		int* cPointer = &c;
		int* dPointer = &d;
		Foo myFoo(a);
		Foo myFoo2(b);
		Foo myFoo3(c);
		Foo myFoo4(d);
		
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mIntVector.PushBack(c);
		mIntVector.PushBack(d);
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mPointerVector.PushBack(cPointer);
		mPointerVector.PushBack(dPointer);
		mFooVector.PushBack(myFoo);
		mFooVector.PushBack(myFoo2);
		mFooVector.PushBack(myFoo3);
		mFooVector.PushBack(myFoo4);

		//Test int
		Vector<int>::Iterator foundIterator = mIntVector.Find(3);
		Vector<int>::Iterator compareIterator(2, &mIntVector);
		TS_ASSERT(foundIterator == compareIterator);

		//Test pointer
		Vector<int*>::Iterator foundPointerIterator = mPointerVector.Find(cPointer);
		Vector<int*>::Iterator comparePointerIterator(2, &mPointerVector);
		TS_ASSERT(foundPointerIterator == comparePointerIterator);

		//Test foo
		Vector<Foo>::Iterator foundFooIterator = mFooVector.Find(myFoo3);
		Vector<Foo>::Iterator compareFooIterator(2, &mFooVector);
		TS_ASSERT(foundFooIterator == compareFooIterator);
	}

	void TestRemove(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;
		int d = 4;
		int e = 5;
		int* aPointer = &a;
		int* bPointer = &b;
		int* cPointer = &c;
		int* dPointer = &d;
		int* ePointer = &e;
		Foo myFoo(a);
		Foo myFoo2(b);
		Foo myFoo3(c);
		Foo myFoo4(d);
		Foo myFoo5(e);


		//Test ints
		//Remove a single element
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mIntVector.PushBack(c);
		TS_ASSERT_EQUALS(mIntVector.Front(), a);
		TS_ASSERT_EQUALS(mIntVector.Back(), c);
		TS_ASSERT_EQUALS(mIntVector.Size(), 3);
		mIntVector.Remove(mIntVector.Find(b));
		TS_ASSERT_EQUALS(mIntVector.Front(), a);
		TS_ASSERT_EQUALS(mIntVector.Back(), c);
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);

		//Range remove
		mIntVector.Clear();
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mIntVector.PushBack(c);
		mIntVector.PushBack(d);
		mIntVector.PushBack(e);
		Vector<int>::Iterator myStartIterator(1, &mIntVector);
		Vector<int>::Iterator myEndIterator(3, &mIntVector);
		mIntVector.Remove(myStartIterator, myEndIterator);
		TS_ASSERT_EQUALS(mIntVector.Front(), a);
		TS_ASSERT_EQUALS(mIntVector.Back(), e);
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);

		//Test pointers
		//Remove a single element
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mPointerVector.PushBack(cPointer);
		TS_ASSERT_EQUALS(mPointerVector.Front(), aPointer);
		TS_ASSERT_EQUALS(mPointerVector.Back(), cPointer);
		TS_ASSERT_EQUALS(mPointerVector.Size(), 3);
		mPointerVector.Remove(mPointerVector.Find(bPointer));
		TS_ASSERT_EQUALS(mPointerVector.Front(), aPointer);
		TS_ASSERT_EQUALS(mPointerVector.Back(), cPointer);
		TS_ASSERT_EQUALS(mPointerVector.Size(), 2);

		//Range Remove
		mPointerVector.Clear();
		mPointerVector.PushBack(aPointer);
		mPointerVector.PushBack(bPointer);
		mPointerVector.PushBack(cPointer);
		mPointerVector.PushBack(dPointer);
		mPointerVector.PushBack(ePointer);
		Vector<int*>::Iterator myStartIterator2(1, &mPointerVector);
		Vector<int*>::Iterator myEndIterator2(3, &mPointerVector);
		mPointerVector.Remove(myStartIterator2, myEndIterator2);
		TS_ASSERT_EQUALS(mPointerVector.Front(), aPointer);
		TS_ASSERT_EQUALS(mPointerVector.Back(), ePointer);
		TS_ASSERT_EQUALS(mPointerVector.Size(), 2);

		//Test Foo
		//Remove a single element
		mFooVector.PushBack(myFoo);
		mFooVector.PushBack(myFoo2);
		mFooVector.PushBack(myFoo3);
		TS_ASSERT_EQUALS(mFooVector.Front(), myFoo);
		TS_ASSERT_EQUALS(mFooVector.Back(), myFoo3);
		TS_ASSERT_EQUALS(mFooVector.Size(), 3);
		mFooVector.Remove(mFooVector.Find(myFoo2));
		TS_ASSERT_EQUALS(mFooVector.Front(), myFoo);
		TS_ASSERT_EQUALS(mFooVector.Back(), myFoo3);
		TS_ASSERT_EQUALS(mFooVector.Size(), 2);

		//Range remove
		mFooVector.Clear();
		mFooVector.PushBack(myFoo);
		mFooVector.PushBack(myFoo2);
		mFooVector.PushBack(myFoo3);
		mFooVector.PushBack(myFoo4);
		mFooVector.PushBack(myFoo5);
		Vector<Foo>::Iterator myFooStartIterator(1, &mFooVector);
		Vector<Foo>::Iterator myFooEndIterator(3, &mFooVector);
		mFooVector.Remove(myFooStartIterator, myFooEndIterator);
		TS_ASSERT_EQUALS(mFooVector.Front(), myFoo);
		TS_ASSERT_EQUALS(mFooVector.Back(), myFoo5);
		TS_ASSERT_EQUALS(mFooVector.Size(), 2);

	}


	void TestRemoveByIndex(void)
	{
		int a = 1;
		int b = 2;
		int c = 3;


		//Test ints
		//Remove a single element
		mIntVector.PushBack(a);
		mIntVector.PushBack(b);
		mIntVector.PushBack(c);
		TS_ASSERT_EQUALS(mIntVector.Front(), a);
		TS_ASSERT_EQUALS(mIntVector.Back(), c);
		TS_ASSERT_EQUALS(mIntVector.Size(), 3);
		mIntVector.Remove(1);
		TS_ASSERT_EQUALS(mIntVector.Front(), a);
		TS_ASSERT_EQUALS(mIntVector.Back(), c);
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);
		mIntVector.Remove(0);
		TS_ASSERT_EQUALS(mIntVector.Front(), c);
		TS_ASSERT_EQUALS(mIntVector.Back(), c);
		TS_ASSERT_EQUALS(mIntVector.Size(), 1);


	}

private:
	Vector<int> mIntVector;
	Vector<int*> mPointerVector;
	Vector<Foo> mFooVector;
};

