#include <cxxtest/TestSuite.h>
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "ActionList.h"

using namespace Library;

class ActionListTestSuite : public CxxTest::TestSuite
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

	//Ensure the name of an actionlist can be initialized correctly
	void TestName(void)
	{
		ActionList al("Movement");
		TS_ASSERT_EQUALS(al.Name(), "Movement");
	}

	//Ensure that the internal scope that contains the actual sub-actions is being generated properly and can be accessed
	void TestGetActions(void)
	{
		ActionList al("Movement");		
		TS_ASSERT_DIFFERS(al.Find("Actions"), nullptr);
	}

	//Test that update doesn't break anything
	void TestUpdate(void)
	{
		ActionList al("Movement");
		WorldState ws;
		TS_ASSERT_THROWS_NOTHING(al.Update(ws));
	}

	//Test that we can adopt action lists into the 'actions' attribute of an entity
	void TestActionInEntity(void)
	{
		ActionList* al = new ActionList("Movement");
		Entity e("Ken");
		al->SetEntity(&e);
		TS_ASSERT_DIFFERS(e.Actions()->Find("Movement"), nullptr);		
		TS_ASSERT_EQUALS(al->GetContainer(), &e);
		delete al;
	}

	//Test that we can create stuff out of our action list factory
	void TestActionFactory(void)
	{
		//The factory is declared and instantiated in a world
		World w;
		
		Action* newAction = Factory<Action>::Create("ActionList")->As<Action>();
		TS_ASSERT_DIFFERS(newAction, nullptr);
		TS_ASSERT_DIFFERS(newAction->Find("Actions"), nullptr);
		TS_ASSERT(newAction->Is("ActionList"));
		
		delete newAction;
	}

	//Test that the entity class can successfully create an action list
	void TestEntityCreateAction(void)
	{

		//World sets up factories
		World w;

		//Entity to generate action list with
		Entity e("Ken");
		e.CreateAction("ActionList", "Movement");
		Scope* a = e.Actions()->Find("Movement")->Get<Scope*>();
		TS_ASSERT_DIFFERS(a, nullptr);
		TS_ASSERT(a->Is("ActionList"));
		TS_ASSERT_EQUALS(a->As<Action>()->Name(), "Movement");
	}


private:
	_CrtMemState startSnapshot;
};