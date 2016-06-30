#include <cxxtest/TestSuite.h>
#include <crtdbg.h>
#include <fstream>
#include <iostream>
#include "XmlParseMaster.h"
#include "ParseHelperFoo.h"

using namespace Library;

class XMLTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif
	}

	void tearDown()
	{
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

	void TestSharedData(void)
	{
		SharedDataFoo s;
		XmlParseMaster m(&s);

		TS_ASSERT_EQUALS(m.GetSharedData(), &s);
		TS_ASSERT_EQUALS(s.GetXmlParseMaster(), &m);

		TS_ASSERT_EQUALS(s.Depth(), 0);
		s.IncrementDepth();
		TS_ASSERT_EQUALS(s.Depth(), 1);
		s.IncrementDepth();
		TS_ASSERT_EQUALS(s.Depth(), 2);
		s.DecrementDepth();
		TS_ASSERT_EQUALS(s.Depth(), 1);
		s.DecrementDepth();
		TS_ASSERT_EQUALS(s.Depth(), 0);


		m.SetSharedData(nullptr);
		TS_ASSERT_EQUALS(m.GetSharedData(), nullptr);
		m.SetSharedData(&s);
		TS_ASSERT_EQUALS(m.GetSharedData(), &s);

	}

	void TestParse(void)
	{	
		SharedDataFoo s;
		XmlParseMaster m(&s);
		ParseHelperFoo p;
		
		m.AddHelper(&p);
		m.Parse("<int>10</int>", 13, false);

		//At this point, one element should be in our sharedDataFoo object. This element is an integer named 'int' with the value 10
		TS_ASSERT_EQUALS(s.Depth(), 0);
		TS_ASSERT_EQUALS(s.mMap.Size(), 1);
		TS_ASSERT(s.mMap.ContainsKey("int"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("int"))).second, 10);
	}

	void TestNestedParse(void)
	{
		SharedDataFoo s;
		XmlParseMaster m(&s);
		ParseHelperFoo p;

		m.AddHelper(&p);
		m.Parse("<player><level>10</level><life>256</life><mana>99</mana></player>", 65, false);

		//At this point, the sharedDataFoo objcet should contain 4 elements. 'player' with a value marked as not yet set (0xffffffff), level = 10, life = 256, mana = 99
		TS_ASSERT_EQUALS(s.Depth(), 0);
		TS_ASSERT_EQUALS(s.mMap.Size(), 4);
		TS_ASSERT(s.mMap.ContainsKey("player"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("player"))).second, 0xffffffff);
		TS_ASSERT(s.mMap.ContainsKey("level"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("level"))).second, 10);
		TS_ASSERT(s.mMap.ContainsKey("life"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("life"))).second, 256);
		TS_ASSERT(s.mMap.ContainsKey("mana"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("mana"))).second, 99);
	}

	void TestAttributes(void)
	{
		SharedDataFoo s;
		XmlParseMaster m(&s);
		ParseHelperFoo p;

		m.AddHelper(&p);
		m.Parse("<int name =\"Ken\" style =\"HokutoShinKen\">10</int>", 48, false);

		/*At this point, one element should be in our sharedDataFoo object. This element is an integer named 'int' with the value 10
		It shouldd also have two attributes logged, name = 'Ken' and style = 'HokutoShinKen'*/
		TS_ASSERT_EQUALS(s.Depth(), 0);
		TS_ASSERT_EQUALS(s.mMap.Size(), 1);
		TS_ASSERT(s.mMap.ContainsKey("int"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("int"))).second, 10);
		TS_ASSERT_EQUALS(s.mName, "Ken");
		TS_ASSERT_EQUALS(s.mStyle, "HokutoShinKen");		
	}

	void TestFile(void)
	{
		SharedDataFoo s;
		XmlParseMaster m(&s);
		ParseHelperFoo p;

		m.AddHelper(&p);

		std::ofstream myFile;
		myFile.open("test.txt");
		myFile << "<int>10</int>";
		myFile.close();
		m.ParseFromFile("test.txt");

		//At this point, one element should be in our sharedDataFoo object. This element is an integer named 'int' with the value 10
		TS_ASSERT_EQUALS(m.GetFileName(), "test.txt");
		TS_ASSERT_EQUALS(s.Depth(), 0);
		TS_ASSERT_EQUALS(s.mMap.Size(), 1);
		TS_ASSERT(s.mMap.ContainsKey("int"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("int"))).second, 10);
	}

	void TestClone(void)
	{
		SharedDataFoo s;
		XmlParseMaster m(&s);
		ParseHelperFoo p;

		m.AddHelper(&p);
		m.Parse("<int>10</int>", 13, false);

		//At this point, one element should be in our sharedDataFoo object. This element is an integer named 'int' with the value 10
		TS_ASSERT_EQUALS(s.Depth(), 0);
		TS_ASSERT_EQUALS(s.mMap.Size(), 1);
		TS_ASSERT(s.mMap.ContainsKey("int"));
		TS_ASSERT_EQUALS((*(s.mMap.Find("int"))).second, 10);

		//Make a clone of m, which will also clone s and p
		XmlParseMaster* mClone = m.Clone();
		SharedDataFoo* cloneData = (SharedDataFoo*)(mClone->GetSharedData());
		TS_ASSERT_EQUALS(cloneData->Depth(), 0);
		TS_ASSERT_EQUALS(cloneData->mMap.Size(), 1);
		TS_ASSERT(cloneData->mMap.ContainsKey("int"));
		TS_ASSERT_EQUALS((*(cloneData->mMap.Find("int"))).second, 10);


		//Destroy the master. It destroys the cloned parse master and sharedData in its destructor
		delete mClone;
	}

	void TestExceptions(void)
	{
		SharedDataFoo s;
		XmlParseMaster m(&s);
		ParseHelperFoo p;

		TS_ASSERT_THROWS_ANYTHING(m.AddHelper(nullptr));
		TS_ASSERT_THROWS_ANYTHING(m.RemoveHelper(nullptr));

		m.AddHelper(&p);

		TS_ASSERT_THROWS_ANYTHING(m.Parse(nullptr, 13, false));
		
	}

private:
	_CrtMemState startSnapshot;

};