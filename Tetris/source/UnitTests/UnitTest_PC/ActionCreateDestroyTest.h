#include <cxxtest/TestSuite.h>
#include "World.h"

using namespace Library;

class ActionCreateDestroyTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
#ifdef _DEBUG
		//Create a snapshot of the current debug heap
		//Used to check for memory leaks
		_CrtMemCheckpoint(&startSnapshot);
#endif
		mCreate = new ActionCreateAction("Creator");
		mDestroy = new ActionDestroyAction("Destroyer");
	}

	void tearDown()
	{
		delete mCreate;
		delete mDestroy;
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


#pragma region ActionCreateActionTests
	//Instantiate an actionCreateAction and ensure that it is initialized appropriately
	void TestInitialization(void)
	{
		TS_ASSERT_EQUALS(mCreate->Name(), "Creator");
	}

	//Ensure that the getters and setters for the prototype name and instance name are working
	void TestGettersAndSetters(void)
	{
		mCreate->SetPrototypeName("ActionList");
		mCreate->SetCreationName("NewList");
		TS_ASSERT_EQUALS(mCreate->GetPrototypeName(), "ActionList");
		TS_ASSERT_EQUALS(mCreate->GetCreationName(), "NewList");
	}

	//Ensure that the ActionCreateAction factory created in world is properly functioning
	void TestFactory(void)
	{
		//World to initialize factory
		World w;
	
		ActionCreateAction* factoryCreated = Factory<Action>::Create("ActionCreateAction")->As<ActionCreateAction>();
		TS_ASSERT_DIFFERS(factoryCreated, nullptr);
		factoryCreated->SetPrototypeName("ActionList");
		factoryCreated->SetCreationName("NewList");
		TS_ASSERT_EQUALS(factoryCreated->GetPrototypeName(), "ActionList");
		TS_ASSERT_EQUALS(factoryCreated->GetCreationName(), "NewList");
		delete factoryCreated;
	}

	//Make sure that we can create these via the actionList and entity create functions
	void TestEntityAndActionListCreate(void)
	{
		//World to initialize factory
		World w;

		Entity e;
		ActionCreateAction* entityCreated = e.CreateAction("ActionCreateAction", "EntityCreated")->As<ActionCreateAction>();
		TS_ASSERT_DIFFERS(entityCreated, nullptr);
		TS_ASSERT_EQUALS(entityCreated->Name(), "EntityCreated");
		TS_ASSERT_EQUALS(entityCreated->GetContainer(), &e);
		TS_ASSERT_EQUALS(entityCreated->GetParent(), e.Actions());
		entityCreated->SetPrototypeName("ActionList");
		entityCreated->SetCreationName("NewList");
		TS_ASSERT_EQUALS(entityCreated->GetPrototypeName(), "ActionList");
		TS_ASSERT_EQUALS(entityCreated->GetCreationName(), "NewList");

		ActionList al;
		ActionCreateAction* actionListCreated = al.CreateAction("ActionCreateAction", "ActionListCreated")->As<ActionCreateAction>();
		TS_ASSERT_DIFFERS(actionListCreated, nullptr);
		TS_ASSERT_EQUALS(actionListCreated->Name(), "ActionListCreated");
		actionListCreated->SetPrototypeName("ActionList");
		actionListCreated->SetCreationName("NewList");
		TS_ASSERT_EQUALS(actionListCreated->GetPrototypeName(), "ActionList");
		TS_ASSERT_EQUALS(actionListCreated->GetCreationName(), "NewList");

	}

	//Test the update function while we are contained by an entity and make sure that the
	//new item is being created and added to the parent scope as expected
	void TestUpdateInEntity(void)
	{
		//World to initialize factory
		World w;

		WorldState ws;

		Entity e("Entity");
		ActionCreateAction* entityCreated = e.CreateAction("ActionCreateAction", "EntityCreated")->As<ActionCreateAction>();
		entityCreated->SetPrototypeName("ActionList");
		entityCreated->SetCreationName("NewList");
		TS_ASSERT_EQUALS(entityCreated->GetContainer(), &e);
		TS_ASSERT_EQUALS(entityCreated->GetParent(), e.Actions());

		e.Update(ws);

		//At this point, entitycreated should have made a new actionlist in the action subscope our entity. It should have the name NewList

		TS_ASSERT_DIFFERS(e.Actions()->Find("NewList"), nullptr);
		TS_ASSERT_EQUALS(e.Actions()->Find("NewList")->Size(), 1);

		ActionList* actionCreated = e.Actions()->Find("NewList")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(actionCreated, nullptr);
		TS_ASSERT_EQUALS(actionCreated->GetContainer(), entityCreated->GetContainer());
	}

	//Test update again, but this time in an actionList
	void TestUpdateInActionList(void)
	{
		//World to initialize factory
		World w;

		WorldState ws;

		ActionList al("Movement");
		ActionCreateAction* actionListCreated = al.CreateAction("ActionCreateAction", "CreateJumpList")->As<ActionCreateAction>();
		actionListCreated->SetPrototypeName("ActionList");
		actionListCreated->SetCreationName("NewList");
		TS_ASSERT_EQUALS(actionListCreated->GetContainer(), &al);
		TS_ASSERT_EQUALS(actionListCreated->GetParent(), al.Actions());

		al.Update(ws);

		//At this point, al should have a new sub-actionList named NewList
		TS_ASSERT_DIFFERS(al.Actions()->Find("NewList"), nullptr);
		TS_ASSERT_EQUALS(al.Actions()->Find("NewList")->Size(), 1);

		ActionList* actionCreated = al.Actions()->Find("NewList")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(actionCreated, nullptr);
		TS_ASSERT_EQUALS(actionCreated->GetContainer(), actionListCreated->GetContainer());
	}
#pragma endregion

#pragma region ActionDestroyActionTests
	
	//Ensure that things initialize fine and we can access our name
	void TestName(void)
	{
		TS_ASSERT_EQUALS(mDestroy->Name(), "Destroyer");
	}

	//Getters and setters
	void TestGetSetTarget(void)
	{
		mDestroy->SetTargetName("NewList");
		TS_ASSERT_EQUALS(mDestroy->GetTargetName(), "NewList");
	}

	//Factory
	void TestDestroyFactory(void)
	{
		//World to initialize factory
		World w;

		ActionDestroyAction* factoryCreated = Factory<Action>::Create("ActionDestroyAction")->As<ActionDestroyAction>();
		TS_ASSERT_DIFFERS(factoryCreated, nullptr);
		factoryCreated->SetTargetName("NewList");
		TS_ASSERT_EQUALS(factoryCreated->GetTargetName(), "NewList");
		delete factoryCreated;
	}

	//Entity and action list create tests
	void TestFactoryInContainers(void)
	{
		//World to initialize factory
		World w;

		Entity e;
		ActionDestroyAction* entityCreated = e.CreateAction("ActionDestroyAction", "EntityCreated")->As<ActionDestroyAction>();
		TS_ASSERT_DIFFERS(entityCreated, nullptr);
		TS_ASSERT_EQUALS(entityCreated->Name(), "EntityCreated");
		TS_ASSERT_EQUALS(entityCreated->GetContainer(), &e);
		TS_ASSERT_EQUALS(entityCreated->GetParent(), e.Actions());
		entityCreated->SetTargetName("NewList");
		TS_ASSERT_EQUALS(entityCreated->GetTargetName(), "NewList");

		ActionList al;
		ActionDestroyAction* actionListCreated = al.CreateAction("ActionDestroyAction", "ActionListCreated")->As<ActionDestroyAction>();
		TS_ASSERT_DIFFERS(actionListCreated, nullptr);
		TS_ASSERT_EQUALS(actionListCreated->Name(), "ActionListCreated");
		actionListCreated->SetTargetName("NewList");
		TS_ASSERT_EQUALS(actionListCreated->GetTargetName(), "NewList");
	}

	//Update in entity
	void TestDestroyUpdateInEntity(void)
	{
		//World to initialize factory
		World w;
		WorldState ws;

		Entity e;
		ActionDestroyAction* entityCreated = e.CreateAction("ActionDestroyAction", "EntityCreated")->As<ActionDestroyAction>();
		e.CreateAction("ActionList", "NewList")->As<ActionList>();
		entityCreated->SetTargetName("NewList");

		e.Update(ws);
		
		TS_ASSERT_EQUALS(e.Actions()->Find("NewList")->Get<Scope*>(), nullptr);
	}

	//Update in action list
	void TestDestroyUpdateInActionList(void)
	{
		//World to initialize factory
		World w;
		WorldState ws;

		ActionList al;
		ActionDestroyAction* actionCreated = al.CreateAction("ActionDestroyAction", "EntityCreated")->As<ActionDestroyAction>();
		al.CreateAction("ActionList", "NewList")->As<ActionList>();
		actionCreated->SetTargetName("NewList");

		al.Update(ws);

		TS_ASSERT_EQUALS(al.Actions()->Find("NewList")->Get<Scope*>(), nullptr);
	}

#pragma endregion

private:
	ActionCreateAction* mCreate;
	ActionDestroyAction* mDestroy;
	_CrtMemState startSnapshot;
};