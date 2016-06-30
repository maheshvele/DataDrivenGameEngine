#include <cxxtest/TestSuite.h>
#include  <string>
#include "Hashmap.h"

using namespace Library;

class HashmapTestSuite : public CxxTest::TestSuite
{
public:

	//Make sure structures are initialized properly
	HashmapTestSuite() :
		mIntHashMap(10), mPointerMap(10), mStringMap(10), mFooMap(10)
	{
	}

	void setUp()
	{
		TS_ASSERT(mIntHashMap.Size() == 0);
	}

	void tearDown()
	{
		mIntHashMap.Clear();
	}

	void TestInsert(void)
	{		
		std::pair<int, int>  intPair(0, 23);
		mIntHashMap.Insert(intPair);
		TS_ASSERT(mIntHashMap.ContainsKey(0));
		TS_ASSERT(!mIntHashMap.ContainsKey(1));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);

		//Confirm that adding an element with the same key shouldn't change anything
		mIntHashMap.Insert(intPair);
		TS_ASSERT(mIntHashMap.ContainsKey(0));
		TS_ASSERT(!mIntHashMap.ContainsKey(1));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);				

	}

	void TestCopy(void)
	{
		std::pair<int, int>  intPair(0, 23);
		mIntHashMap.Insert(intPair);

		//Test assignment operator
		Hashmap<int, int> copyMap = mIntHashMap;
		TS_ASSERT_EQUALS(copyMap.Size(), mIntHashMap.Size());
		TS_ASSERT_EQUALS(copyMap[0], 23);

		//Test copy
		Hashmap<int, int> anotherCopyMap(mIntHashMap);
		TS_ASSERT_EQUALS(anotherCopyMap.Size(), mIntHashMap.Size());
		TS_ASSERT_EQUALS(anotherCopyMap[0], 23);

	}

	void TestIndex(void)
	{
		std::pair<int, int>  intPair(0, 23);
		std::pair<int, int> intPair2(1, 99);
		mIntHashMap.Insert(intPair);
		mIntHashMap.Insert(intPair2);
		TS_ASSERT(mIntHashMap.ContainsKey(0));
		TS_ASSERT(mIntHashMap.ContainsKey(1));

		//Test index operator
		TS_ASSERT_EQUALS(mIntHashMap[0], 23)
		TS_ASSERT_EQUALS(mIntHashMap[1], 99)
	}

	void TestRemove(void)
	{
		std::pair<int, int>  intPair(0, 23);
		mIntHashMap.Insert(intPair);
		TS_ASSERT(mIntHashMap.ContainsKey(0));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);

		//Test remove
		mIntHashMap.Remove(0);
		TS_ASSERT(!mIntHashMap.ContainsKey(0));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
	}

	void TestClear(void)
	{
		//Test clear
		std::pair<int, int>  intPair(0, 23);
		std::pair<int, int>  intPair2(1, 99);
		mIntHashMap.Insert(intPair);
		mIntHashMap.Insert(intPair2);
		TS_ASSERT(mIntHashMap.ContainsKey(0));
		TS_ASSERT(mIntHashMap.ContainsKey(1));
		TS_ASSERT(!mIntHashMap.ContainsKey(2));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);
		TS_ASSERT_EQUALS(mIntHashMap[0], 23);
		TS_ASSERT_EQUALS(mIntHashMap[1], 99);

		mIntHashMap.Clear();
		TS_ASSERT(!mIntHashMap.ContainsKey(0));
		TS_ASSERT(!mIntHashMap.ContainsKey(1));
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);

	}

	

	//Test pointer functor
	void TestPointer(void)
	{
		int a = 1;
		int b = 2;

		int* ap = &a;
		int* bp = &b;

		std::pair<int*, int>  ptrPair(ap, a);
		std::pair<int*, int>  ptrPair2(bp, b);

		mPointerMap.Insert(ptrPair);
		mPointerMap.Insert(ptrPair2);
		TS_ASSERT_EQUALS(mPointerMap.Size(), 2);
		TS_ASSERT(mPointerMap.ContainsKey(ap));
		TS_ASSERT(mPointerMap.ContainsKey(bp));

		
		TS_ASSERT_EQUALS((*(mPointerMap.Find(ap))).second, 1);
		TS_ASSERT_EQUALS((*(mPointerMap.Find(bp))).second, 2);

		mPointerMap.Clear();
		TS_ASSERT_EQUALS(mPointerMap.Size(), 0);
	}

	void TestIterator(void)
	{
	//Test derference
	std::pair<int, int>  intPair(0, 23);
	std::pair<int, int>  intPair2(1, 99);
	mIntHashMap.Insert(intPair);
	mIntHashMap.Insert(intPair2);
	Hashmap<int, int>::Iterator mIntIterator(0, &mIntHashMap);
	Hashmap<int, int>::Iterator mCopyIntIterator(mIntIterator);
	TS_ASSERT_EQUALS((*mIntIterator).second, 23);

	//Test comparison with copy
	TS_ASSERT(mIntIterator == mCopyIntIterator);


	//Test increment (prefix)
	++mIntIterator;
	TS_ASSERT_EQUALS((*mIntIterator).second, 99);

	//Test increment (postfix)
	TS_ASSERT_EQUALS((*(mIntIterator++)).second, 99);
	TS_ASSERT_EQUALS(mIntIterator, mIntHashMap.end());

	//Test comparison
	Hashmap<int, int>::Iterator mOtherIntIterator(1, &mIntHashMap);
	TS_ASSERT(mCopyIntIterator != mOtherIntIterator);

	//Test begin and end
	TS_ASSERT(mIntIterator != mIntHashMap.begin());
	TS_ASSERT(mIntIterator == mIntHashMap.end());

	//Test find
	TS_ASSERT_EQUALS(mCopyIntIterator, mIntHashMap.Find(0));

	//Test operator ->
	TS_ASSERT_EQUALS((*mCopyIntIterator).second, 23);
	mCopyIntIterator->second = 99;
	TS_ASSERT_DIFFERS((*mCopyIntIterator).second, 23);
	TS_ASSERT_EQUALS((*mCopyIntIterator).second, 99);
	}

	//Test string functor
	void  TestString(void)
	{
		std::string s = "Hello";
		std::string s2 = "World";

		std::pair<std::string, int>  strPair(s, 0);
		std::pair<std::string, int>  strPair2(s2, 1);

		mStringMap.Insert(strPair);
		mStringMap.Insert(strPair2);
		TS_ASSERT_EQUALS(mStringMap.Size(), 2);
		TS_ASSERT(mStringMap.ContainsKey(s));
		TS_ASSERT(mStringMap.ContainsKey(s2));

		TS_ASSERT_EQUALS((*mStringMap.Find(s)).second, 0);
		TS_ASSERT_EQUALS((*mStringMap.Find(s2)).second, 1);

		mStringMap.Clear();
		TS_ASSERT_EQUALS(mStringMap.Size(), 0);
	}

	//Test the foo functor
	void TestFoo(void)
	{
		Foo f(1);
		Foo f2(2);

		std::pair<Foo, int> pair(f, 10);
		std::pair<Foo, int> pair2(f2, 20);

		mFooMap.Insert(pair);
		mFooMap.Insert(pair2);
		TS_ASSERT_EQUALS(mFooMap.Size(), 2);
		TS_ASSERT(mFooMap.ContainsKey(f));
		TS_ASSERT(mFooMap.ContainsKey(f2));

		TS_ASSERT_EQUALS((*mFooMap.Find(f)).second, 10);
		TS_ASSERT_EQUALS((*mFooMap.Find(f2)).second, 20);

		mFooMap.Clear();
		TS_ASSERT_EQUALS(mFooMap.Size(), 0);
	}

private:
	Hashmap<int, int> mIntHashMap;
	Hashmap<int*, int> mPointerMap;
	Hashmap<std::string, int> mStringMap;
	Hashmap<Foo, int> mFooMap;
};