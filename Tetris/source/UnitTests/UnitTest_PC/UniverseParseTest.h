#include <cxxtest/TestSuite.h>
#include <crtdbg.h>
#include <fstream>
#include "XMLParseHelperUniverse.h"
#include "XMLParseHelperTable.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"

using namespace Library;

class UniverseParseTestSuite : public CxxTest::TestSuite
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

	//Ensure that the start and end handlers are working for a single world. Ensure tha the name attribute is being read corretly
	void TestParseWorld(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		char* string = "<world name=\"Earth\"></world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));
		TS_ASSERT_EQUALS(sdw.Depth(), 0);
		TS_ASSERT_EQUALS(w.Name(), "Earth");
	}

	//Test parsing a single sector in the world 
	void TestSingleSector(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		
		//At this time, there should be no sectors in the child scope
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\"><sector name=\"Florida\"></sector></world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain a single empty sector (Florida)
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 1);
		Sector* sectorAddress = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(sectorAddress, nullptr);
		TS_ASSERT_EQUALS(sectorAddress->Name(), "Florida");
	}

	//Test parsing multiple sectors in the world
	void TestMultipleSectors(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);


		//At this time, there should be no sectors in the child scope
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\"><sector name=\"Florida\"></sector><sector name=\"Vegas\"></sector></world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain two empty sectors  (Florida and  Vegas)
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 2);
		Sector* sectorAddress1 = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(sectorAddress1, nullptr);
		TS_ASSERT_EQUALS(sectorAddress1->Name(), "Florida");
		Sector* sectorAddress2 = w.Sectors()->Find("Vegas")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(sectorAddress2, nullptr);
		TS_ASSERT_EQUALS(sectorAddress2->Name(), "Vegas");
	}

	//Test parsing a single entity in a sector
	void TestSingleEntity(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);


		//At this time, there should be no sectors in the child scope
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\"><sector name=\"Florida\"><entity class=\"Entity\" name=\"Ken\"></entity></sector></world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain one sector (Florida) that contains one  entity (Ken)
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 1);
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();		
		TS_ASSERT_DIFFERS(Florida, nullptr);
		TS_ASSERT_EQUALS(Florida->Name(), "Florida");
		TS_ASSERT_DIFFERS(Florida->Entities()->Find("Ken"), nullptr);
		TS_ASSERT_EQUALS(Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>()->Name(), "Ken");
	}

	//Test parsing multiple entities in the same sector
	void TestMultipleEntities(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);


		//At this time, there should be no sectors in the child scope
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\"><sector name=\"Florida\"><entity class=\"Entity\" name=\"Ken\"></entity><entity class=\"Entity\" name=\"Paul\"></entity></sector></world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain one sector (Florida) that contains two entities (Ken and Paul)
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 1);
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);
		TS_ASSERT_EQUALS(Florida->Name(), "Florida");
		TS_ASSERT_DIFFERS(Florida->Entities()->Find("Ken"), nullptr);
		TS_ASSERT_EQUALS(Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>()->Name(), "Ken");
		TS_ASSERT_DIFFERS(Florida->Entities()->Find("Paul"), nullptr);
		TS_ASSERT_EQUALS(Florida->Entities()->Find("Paul")->Get<Scope*>()->As<Entity>()->Name(), "Paul");
	}

	//Test parsing multiple entities in different sectors
	void TestMultipleEntitiesAndSectors(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		//At this time, there should be no sectors in the child scope
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\"><sector name=\"Florida\"><entity class=\"Entity\" name=\"Ken\"></entity></sector><sector name=\"Vegas\"><entity class=\"Entity\" name=\"Paul\"></entity></sector></world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain two sectors (Vegas and Florida). Vegas should contain an entity (Paul) and Florida should contain another entity (Ken)
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 2);
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);
		TS_ASSERT_EQUALS(Florida->Name(), "Florida");
		TS_ASSERT_DIFFERS(Florida->Entities()->Find("Ken"), nullptr);
		TS_ASSERT_EQUALS(Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>()->Name(), "Ken");

		Sector* Vegas = w.Sectors()->Find("Vegas")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Vegas, nullptr);
		TS_ASSERT_EQUALS(Vegas->Name(), "Vegas");
		TS_ASSERT_DIFFERS(Vegas->Entities()->Find("Paul"), nullptr);
		TS_ASSERT_EQUALS(Vegas->Entities()->Find("Paul")->Get<Scope*>()->As<Entity>()->Name(), "Paul");
	}

	//Test filling out an entity using our table parser
	void TestFilledEntity(void)
	{
		Entity e("Ken");
		XMLParseHelperTable::SharedDataScope s(&e);
		XmlParseMaster m(&s);
		XMLParseHelperTable p;

		m.AddHelper(&p);
		char* string = "<table><integer name=\"HP\" index=\"0\">10</integer></table>";
		int length = strlen(string);
		m.Parse(string, length, false);

		//The scope sc should now contain a single datum of type integer with one value of 10 at index zero and the name "Ken"
		Datum* cachedDatum = e.Find("HP");
		TS_ASSERT_EQUALS(cachedDatum->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(cachedDatum->Size(), 1);
		TS_ASSERT_EQUALS(cachedDatum->Get<int>(), 10);
	}

	//Test adding a datum to our entity when it is within a full world system using the chain of responsibility
	void TestTableParserWithWorld(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperTable t;
		m.AddHelper(&p);
		m.AddHelper(&t);

		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<integer name = \"HP\" index=\"0\">10</integer>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		Sector* florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* ken = florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		Datum* HP = ken->Find("HP");
		
		TS_ASSERT_EQUALS(HP->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(HP->Get<int>(), 10);
	}

	void TestWindowWithWorld(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperTable t;
		m.AddHelper(&p);
		m.AddHelper(&t);

		char* string = "<world name=\"Earth\">"
							"<window name=\"Tetris Gaiden Attack\" width=\"1200\" height=\"700\">"
							"</window>"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<integer name = \"HP\" index=\"0\">10</integer>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));
		
		sf::RenderWindow* window = w.GetWindow();
		TS_ASSERT_DIFFERS(window, nullptr);
	}

	//Test setting local newly declared variables to other variables in the same scope
	void TestDeclareVariables(void)
	{
		/*World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperTable t;
		XMLParseHelperUniverse p;
		m.AddHelper(&p);
		m.AddHelper(&t);

		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<integer name = \"HP\">10</integer>"
									"<integer name = \"CurHP\">HP</integer>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);*/

	}

private:
	_CrtMemState startSnapshot;

};