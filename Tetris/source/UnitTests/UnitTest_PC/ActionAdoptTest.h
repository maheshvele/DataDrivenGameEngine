#include <cxxtest/TestSuite.h>
#include "World.h"
#include "ActionAdopt.h"
#include "XMLParseHelperUniverse.h"
#include "XMLParseHelperExpression.h"

using namespace Library;

class ActionAdoptTestSuite : public CxxTest::TestSuite
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


	//Instantiate an action and test its getters and setters
	void TestInitialization(void)
	{
		ActionAdopt aa;

		Datum* targetDatum = aa.Find("Target");

		TS_ASSERT_DIFFERS(targetDatum, nullptr);

		aa.SetTargetSector("s");

		TS_ASSERT_EQUALS("s", aa.GetTargetSector());
	}

	//Test the update function
	void TestUpdate(void)
	{
		World w;
		WorldState ws;
		Sector* s = new Sector("TargetSector");
		Sector* s2 = new Sector("OldSector");
		Entity* e = new Entity("ContainerEntity");

		s->SetWorld(&w);
		s2->SetWorld(&w);
		e->SetSector(s2);

		ActionAdopt* aa = new ActionAdopt("Action");
		aa->SetTargetSector("TargetSector");
		aa->SetEntity(e);

		/*
		At this point, the world should contain two sectors: OldSector and TargetSector. OldSector should contain
		a single entity with the name 'ContainerEntity'. This container entity holds our ActionAdopt (named simply
		'Action' in this case). The expected behavior on update is that the actionAdopt will force the sector that
		goes by the name 'TargetSector' to adopt 'ContainerEntity', taking it away from 'OldSector'
		*/

		//Check that oldsector currently contains containerEntity
		Scope* container = s2->Entities()->Find("ContainerEntity")->Get<Scope*>();
		TS_ASSERT_DIFFERS(container, nullptr);
		TS_ASSERT_EQUALS(container, e);

		//Update
		TS_ASSERT_THROWS_NOTHING(w.Update(ws));
		
		//TargetSector should now contain containerEntity
		container = s->Entities()->Find("ContainerEntity")->Get<Scope*>();
		TS_ASSERT_DIFFERS(container, nullptr);
		TS_ASSERT_EQUALS(container, e);


		//OldSector should no longer have containerEntity
		container = s2->Entities()->Find("ContainerEntity")->Get<Scope*>();
		TS_ASSERT_EQUALS(container, nullptr);
	}

	//Test the factory
	void TestFactory(void)
	{
		//Initialize stuff in world
		World w;

		///Create a new ActionCreateEntity using the factory
		ActionAdopt* factoryCreated = Factory<Action>::Create("ActionAdopt")->As<ActionAdopt>();
		TS_ASSERT_DIFFERS(factoryCreated, nullptr);

		//Double check getting/setting the target name
		factoryCreated->SetTargetSector("target");

		TS_ASSERT_EQUALS("target", factoryCreated->GetTargetSector());
		delete factoryCreated;
	}

	//Test an xml parse
	void TestParse(void)
	{
		//Expected behavior after update: the entity Ken is orphaned from Florida and adopted to Lordran
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
									"<action name=\"AdoptAction\" class=\"ActionAdopt\" target=\"Lordran\">"
									"</action>"
								"</entity>"
							"</sector>"
							"<sector name=\"Lordran\">"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Get the sectors
		Scope* sectors = w.Sectors();
		Sector* Florida = sectors->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);

		Sector* Lordran = sectors->Find("Lordran")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Lordran, nullptr);

		//Get the entity
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_DIFFERS(Ken, nullptr);

		//Get the action
		Action* a = Ken->Actions()->Find("AdoptAction")->Get<Scope*>()->As<Action>();
		TS_ASSERT_DIFFERS(a, nullptr);

		//Ensure that the action is of the correct type and was initialized as expected
		ActionAdopt* aa = a->As<ActionAdopt>();
		TS_ASSERT_DIFFERS(aa, nullptr);
		
		////Ensure that the update call doesn't break anything and that the entity changes its containing sector correctly
		TS_ASSERT_THROWS_NOTHING(w.Update(ws));

		//Check that Lordran now contains Ken
		Ken = Lordran->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_DIFFERS(Ken, nullptr);

		//Check that Florida no longer contains Ken
		Scope* Empty = Florida->Entities()->Find("Ken")->Get<Scope*>();
		TS_ASSERT_EQUALS(Empty, nullptr);
	}


private:
	_CrtMemState startSnapshot;
};