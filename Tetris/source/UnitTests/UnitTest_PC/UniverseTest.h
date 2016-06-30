#include <cxxtest/TestSuite.h>
#include "Entity.h"
#include "Sector.h"
#include "World.h"

using namespace Library;

class UniverseTestSuite : public CxxTest::TestSuite
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

	//Ensure that names get created correctly for entities and sectors
	void TestNames(void)
	{
		Entity e("Ken");
		TS_ASSERT_EQUALS(e.Name(), "Ken");
		Sector s("Lordran");
		TS_ASSERT_EQUALS(s.Name(), "Lordran");
		World w;
		w.SetName("Dark Souls");
		TS_ASSERT_EQUALS(w.Name(), "Dark Souls");
	}

	//Ensure that the getters and setters of the world state are functioning
	void TestWorldState(void)
	{
		Entity* e = new Entity("Ken");
		Sector* s = new Sector("Lordran");
		World* w = new World();
		WorldState ws;

		ws.SetEntity(e);
		ws.SetSector(s);
		ws.SetWorld(w);

		TS_ASSERT_EQUALS(ws.GetEntity(), e);
		TS_ASSERT_EQUALS(ws.GetSector(), s);
		TS_ASSERT_EQUALS(ws.GetWorld(), w);

		delete e;
		delete s;
		delete w;
	}

	//Test that the world updates its current state as expected
	void TestWorldCurState(void)
	{
		Entity* e = new Entity("Ken");
		Sector* s = new Sector("Lordran");
		World* w = new World();
		WorldState ws;

		ws.SetEntity(e);
		ws.SetSector(s);
		ws.SetWorld(w);

		w->SetWorldState(ws);
		TS_ASSERT_EQUALS(ws.GetEntity(), w->GetWorldState().GetEntity());
		TS_ASSERT_EQUALS(ws.GetSector(), w->GetWorldState().GetSector());
		TS_ASSERT_EQUALS(ws.GetWorld(), w->GetWorldState().GetWorld());

		delete e;
		delete s;
		delete w;
	}

	//Instantiate some entities and link them to a sector
	void TestEntityInSector(void)
	{
		Entity* e = new Entity("Ken");
		Sector s("Lordran");

		e->SetSector((Scope*)&s);
		TS_ASSERT_EQUALS(&s, e->GetSector());
		TS_ASSERT_DIFFERS(nullptr, s.Entities()->Find("Ken"));
		TS_ASSERT_EQUALS(e, s.Entities()->Find("Ken")->Get<Scope*>());
	}

	//Instantiate some sectors and link them to a world
	void TestSectorsInWorld(void)
	{
		World w;
		Sector* s = new Sector("Lordran");
		s->SetWorld(&w);
		TS_ASSERT_EQUALS(&w, s->GetWorld());
		TS_ASSERT_DIFFERS(nullptr, w.Sectors()->Find("Lordran"));
		TS_ASSERT_EQUALS(s, w.Sectors()->Find("Lordran")->Get<Scope*>());
	}

	//Test having a sector create a new entity
	void TestCreateEntity(void)
	{
		World w; //Even though it is not used here, the factories are instantiated in world. As such, entities cannot be created until we instantiate a world.
		Sector s;
		Scope* e = s.CreateEntity("Entity","Ken");
		TS_ASSERT(e->Is("Entity"));
		TS_ASSERT_DIFFERS(s.Entities()->Find("Ken"), nullptr);
	}

	//Test having a world create a new sector
	void TestCreateSector(void)
	{
		World w;
		Scope* s = w.CreateSector("Orlando");
		TS_ASSERT(s->Is("Sector"));
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Orlando"), nullptr);
	}

	//Test the update chain
	void TestUpdate(void)
	{
		World w;
		Sector* s = w.CreateSector("Orlando")->As<Sector>();
		Entity* e = s->CreateEntity("Entity", "Ken")->As<Entity>();
		TS_ASSERT_DIFFERS(s, nullptr);
		TS_ASSERT_DIFFERS(e, nullptr);
		WorldState ws;
		TS_ASSERT_THROWS_NOTHING(w.Update(ws));
	}

	/*
	This was a test for my first pass at copying entities. Leaving it in here for the case that
	we may return to it one day where a use case presents itself for copying entities, making it
	necessary to revisit this code.

	//Test copy constructor and copy assingment operator for entity
	void UnusedTestCopyEntity(void)
	{
		//Test copy constructor
		Entity e("Ken");
		Datum& d = e.Append("Accuracy");
		d.SetType(Datum::FLOAT);
		d.Set(0.87f);
		Entity eCopy(e);
		TS_ASSERT_EQUALS(eCopy.Name(), e.Name());
		TS_ASSERT_DIFFERS(eCopy.Find("Accuracy"), nullptr);
		TS_ASSERT_DIFFERS(eCopy.Find("Accuracy"), &d);
		TS_ASSERT_EQUALS(eCopy.Find("Accuracy")->Get<float>(), d.Get<float>());

		//Test copy assignment
		Entity eAssign("NotKen");
		eAssign = e;
		TS_ASSERT_DIFFERS(eAssign.Name(), "NotKen");
		TS_ASSERT_EQUALS(eAssign.Name(), e.Name());
		TS_ASSERT_DIFFERS(eAssign.Find("Accuracy"), nullptr);
		TS_ASSERT_DIFFERS(eAssign.Find("Accuracy"), &d);
		TS_ASSERT_DIFFERS(eAssign.Find("Accuracy"), eCopy.Find("Accuracy"));
		TS_ASSERT_EQUALS(eAssign.Find("Accuracy")->Get<float>(), d.Get<float>());

	}*/

private:
	_CrtMemState startSnapshot;
};