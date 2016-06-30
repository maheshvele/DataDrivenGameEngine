#include <cxxtest/TestSuite.h>
#include <crtdbg.h>
#include "XMLParseHelperTable.h"
#include "SharedDataFoo.h"

using namespace Library;

ExternalConcreteFactory(RTTI, SharedDataScope, XMLParseHelperTable)

ConcreteFactory(RTTI, SharedDataFoo)

class FactoryTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif


		mSharedDataScopeFactory = new SharedDataScopeFactory();

	}

	void tearDown()
	{

		delete mSharedDataScopeFactory;

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

	//Ensure that shared data scope factory knows its own name
	void TestName(void)
	{
		TS_ASSERT_EQUALS(mSharedDataScopeFactory->ClassName(), "SharedDataScope");
	}

	//Ensure that the factory is registers itself successfully
	void TestFind(void)
	{
		//See if mSharedDataScopeFactory registered itself correctly
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("SharedDataScope"), mSharedDataScopeFactory);

		//Ensure that the expected behavior occurs when we search for something that isn't registered
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("KenDataKen"), nullptr);
	}

	//Ensure that the factory can create new instances successfully.
	//This test does some xml parsing stuff to make sure that the SharedDataScope that is created is functional
	void TestCreate(void)
	{
		RTTI* created;
		created = mSharedDataScopeFactory->Create();
		
		TS_ASSERT(created->Is("SharedDataScope"));

		if (created->Is("SharedDataScope"))
		{
			XMLParseHelperTable::SharedDataScope* reinterpereted = created->As<XMLParseHelperTable::SharedDataScope>();//reinterpret_cast<XMLParseHelperTable::SharedDataScope*>(created);

			Scope sc(10);
			reinterpereted->SetScope(&sc);

			XmlParseMaster m(reinterpereted);
			XMLParseHelperTable p;

			m.AddHelper(&p);
			char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer></table>";
			int length = strlen(string);
			m.Parse(string, length, false);

			//The scope sc should now contain a single datum of type integer with one value of 10 at index zero and the name "Ken"
			Datum* cachedDatum = sc.Find("Ken");
			TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
			TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
			TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);

		}

		delete created;
	}

	//Ensure that we can create instances from class names
	void TestCreateFromName(void)
	{
		RTTI* created;
		created = Factory<RTTI>::Create("SharedDataScope");

		TS_ASSERT(created->Is("SharedDataScope"));

		if (created->Is("SharedDataScope"))
		{
			XMLParseHelperTable::SharedDataScope* reinterpereted = created->As<XMLParseHelperTable::SharedDataScope>();//reinterpret_cast<XMLParseHelperTable::SharedDataScope*>(created);

			Scope sc(10);
			reinterpereted->SetScope(&sc);

			XmlParseMaster m(reinterpereted);
			XMLParseHelperTable p;

			m.AddHelper(&p);
			char* string = "<table><integer name=\"Ken\" index=\"0\">10</integer></table>";
			int length = strlen(string);
			m.Parse(string, length, false);

			//The scope sc should now contain a single datum of type integer with one value of 10 at index zero and the name "Ken"
			Datum* cachedDatum = sc.Find("Ken");
			TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
			TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
			TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);

		}

		delete created;
	}

	//Test begin
	void TestBegin(void)
	{
		//mSharedDataScopeFactory should be the only thing registered with the abstract factory right now
		TS_ASSERT_EQUALS((*(SharedDataScopeFactory::begin())).first, "SharedDataScope");
	}

	//Test end
	void TestEnd(void)
	{
		//End returns an iterator passed the final factory. As such, trying to dereference it should throw an exception
		TS_ASSERT_THROWS_ANYTHING(*(SharedDataScopeFactory::end()));
	}

	//Ensure that we can iterate through our list of factories with begin and end
	void TestIteration(void)
	{
		//Foofactory
		SharedDataFooFactory* fooFactory = new SharedDataFooFactory();

		TS_ASSERT_EQUALS(fooFactory->ClassName(), "SharedDataFoo");

		//Make sure both factories are in the factory list
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("SharedDataScope"), mSharedDataScopeFactory);
		TS_ASSERT_EQUALS(Factory<RTTI>::Find("SharedDataFoo"), fooFactory);
		
		//Ensure we can reach all of the items via iteration
		Hashmap<std::string, Factory<RTTI>*>::Iterator i = SharedDataScopeFactory::begin();
		TS_ASSERT_EQUALS((*i).first, "SharedDataFoo");
		TS_ASSERT_EQUALS((*i).second, fooFactory);
		++i;
		TS_ASSERT_EQUALS((*i).first, "SharedDataScope");
		TS_ASSERT_EQUALS((*i).second, mSharedDataScopeFactory);
		++i;
		TS_ASSERT_EQUALS(i, SharedDataScopeFactory::end());
		TS_ASSERT_THROWS_ANYTHING(*i);

		delete fooFactory;
	}

private:
	_CrtMemState startSnapshot;
	SharedDataScopeFactory* mSharedDataScopeFactory;
};