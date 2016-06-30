#include <cxxtest/TestSuite.h>
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "ActionWhile.h"
#include "SharedDataWorld.h"
#include "XMLParseHelperWhile.h"
#include "XMLParseHelperExpression.h"
#include "XMLParseHelperUniverse.h"

using namespace Library;

class ActionWhileTestSuite : public CxxTest::TestSuite
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

	//Ensure the name of an ActionWhile can be initialized correctly
	void TestName(void)
	{
		ActionWhile al("Movement");
		TS_ASSERT_EQUALS(al.Name(), "Movement");

		al["Condition"] = 1;
	}

	//Ensure that the internal scope that contains the actual sub-actions is being generated properly and can be accessed
	void TestGetActions(void)
	{
		ActionWhile al("Movement");
		TS_ASSERT_DIFFERS(al.Find("Actions"), nullptr);
	}

	//Test that update doesn't break anything
	void TestUpdate(void)
	{
		ActionWhile al("Movement");
		WorldState ws;
		TS_ASSERT_THROWS_NOTHING(al.Update(ws));
	}

	//Test that we can adopt action lists into the 'actions' attribute of an entity
	void TestActionInEntity(void)
	{
		ActionWhile* al = new ActionWhile("Movement");
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

		Action* newAction = Factory<Action>::Create("ActionWhile")->As<Action>();
		TS_ASSERT_DIFFERS(newAction, nullptr);
		TS_ASSERT_DIFFERS(newAction->Find("Actions"), nullptr);
		TS_ASSERT(newAction->Is("ActionWhile"));

		delete newAction;
	}

	//Test that the entity class can successfully create an action list
	void TestEntityCreateAction(void)
	{

		//World sets up factories
		World w;

		//Entity to generate action list with
		Entity e("Ken");
		e.CreateAction("ActionWhile", "Movement");
		Scope* a = e.Actions()->Find("Movement")->Get<Scope*>();
		TS_ASSERT_DIFFERS(a, nullptr);
		TS_ASSERT(a->Is("ActionWhile"));
		TS_ASSERT_EQUALS(a->As<Action>()->Name(), "Movement");
	}


	void TestActionWhile(void)
	{
		ActionWhile* al = new ActionWhile("If");
		Entity e("Anthony");
		al->SetEntity(&e);

		TS_ASSERT_DIFFERS(e.Actions()->Find("If"), nullptr);
		TS_ASSERT_EQUALS(al->GetContainer(), &e);

		delete al;
	}


	void TestXMLParse(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperExpression pe;
		XMLParseHelperUniverse pu;
		XMLParseHelperWhile p;
		XMLParseHelperTable pt;
		m.AddHelper(&p);
		m.AddHelper(&pe);
		m.AddHelper(&pu);
		m.AddHelper(&pt);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string =		"<world name=\"Earth\">"
								"<sector name=\"Florida\">"
									"<entity class=\"Entity\" name=\"Ken\">"
										"<integer name=\"Condition\">3</integer>"
										"<action name=\"While\" class=\"ActionWhile\" type=\"variable\" condition=\"Condition\">"
											"<action name=\"Expression\" class=\"ActionExpression\">"
												"this.Condition = this.Condition - 1"
											"</action>"
										"</action>"
									"</entity>"
								"</sector>"
							"</world>";

		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain one sector (Florida) that contains one  entity (Ken) which knows one actionList (movement)
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		ActionList* actionWhile = Ken->Actions()->Find("While")->Get<Scope*>()->As<ActionList>();
		Action* actionExpression = actionWhile->Actions()->Find("Expression")->Get<Scope*>()->As<Action>();

		TS_ASSERT_EQUALS((*actionWhile).Name(), "While");
		TS_ASSERT_EQUALS((*actionExpression).Name(), "Expression");

		std::cout << "\nActionWhile Began...\n-----------------\n" << std::endl;
		WorldState ws;
		w.Update(ws);
		// Because 'Condition' is set to 5, have a while loop that evaluates 5 times
		actionWhile->Find("Condition")->Set(5);
		w.Update(ws);
		// Because 'Condition' is set to 15, have a while loop that evaluates 15 times
		actionWhile->Find("Condition")->Set(15);
		w.Update(ws);
	}


private:
	_CrtMemState startSnapshot;
};