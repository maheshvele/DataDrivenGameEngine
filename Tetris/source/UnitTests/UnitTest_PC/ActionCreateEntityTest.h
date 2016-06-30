#include <cxxtest/TestSuite.h>
#include "World.h"
#include "ActionCreateEntity.cpp"
#include "XMLParseHelperUniverse.h"
#include "XMLParseHelperExpression.h"
#include "Sector.h"

using namespace Library;

class ActionCreateEntityTest : public CxxTest::TestSuite
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

	//Instantiate an ActionCreateEntity and ensure that it is initialized appropriately by messing with the getters and setters
	void TestGetSet(void)
	{
		ActionCreateEntity ace;

		//Ensure that we have the default class name 'Entity'
		TS_ASSERT_EQUALS(ace.GetClass(), "Entity");

		//Set the instance name to be block1
		ace.SetInstanceName("block1");

		//Ensure that we can retrieve the instance name correctly
		TS_ASSERT_EQUALS(ace.GetInstanceName(), "block1");		
	}

	//Test that the update function creates a new entity as expected
	void TestUpdate(void)
	{
		ActionCreateEntity ace;
		Sector s;
		Entity e;
		WorldState ws;
		World w;//Set up the factories
		e.SetSector(&s);
		ace.SetEntity(&e);

		ace.SetInstanceName("Ken");

		ace.Update(ws);

		//Grab the entity that we created, and make sure it exists
		Scope* Ken = s.Entities()->Find("Ken")->Get<Scope*>();

		TS_ASSERT_DIFFERS(Ken, nullptr);

		ace.Orphan();
		e.Orphan();
	}

	//Test Factory
	void TestFactory(void)
	{
		//Initialize stuff in world
		World w;

		///Create a new ActionCreateEntity using the factory
		ActionCreateEntity* factoryCreated = Factory<Action>::Create("ActionCreateEntity")->As<ActionCreateEntity>();
		TS_ASSERT_DIFFERS(factoryCreated, nullptr);

		//Ensure that we have the default class name 'Entity'
		TS_ASSERT_EQUALS(factoryCreated->GetClass(), "Entity");

		//Set the instance name to be block1
		factoryCreated->SetInstanceName("block1");

		//Ensure that we can retrieve the instance name correctly
		TS_ASSERT_EQUALS(factoryCreated->GetInstanceName(), "block1");
		delete factoryCreated;
	}

	//Test parsing an ActinCreateEntity
	void TestParse(void)
	{
		World w;
		WorldState ws;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"EntityCreator\" class=\"ActionCreateEntity\" instanceName=\"CreatedEntity\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Get the sector
		Scope* sectors = w.Sectors();
		Sector* Florida = sectors->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);

		//Get the entity
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_DIFFERS(Ken, nullptr);

		//Get the action
		Action* a = Ken->Actions()->Find("EntityCreator")->Get<Scope*>()->As<Action>();
		TS_ASSERT_DIFFERS(a, nullptr);
		
		//Ensure that the aciton is of the correct type and was initialized as expected
		ActionCreateEntity* creator = a->As<ActionCreateEntity>();
		TS_ASSERT_DIFFERS(creator, nullptr);
		TS_ASSERT_EQUALS(creator->GetClass(), "Entity");
		TS_ASSERT_EQUALS(creator->GetInstanceName(), "CreatedEntity");

		//Ensure that the entity gets created in Florida after the update
		w.Update(ws);

		Entity* created = Florida->Entities()->Find("CreatedEntity")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_DIFFERS(created, nullptr);
	}


private:
	_CrtMemState startSnapshot;
};