#include <cxxtest/TestSuite.h>
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "ActionIf.h"
#include "SharedDataWorld.h"
#include "XMLParseHelperIf.h"
#include "XMLParseHelperExpression.h"
#include "XMLParseHelperUniverse.h"

using namespace Library;

class ActionIfTestSuite : public CxxTest::TestSuite
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

	//Ensure the name of an ActionIf can be initialized correctly
	void TestName(void)
	{
		ActionIf al("Movement");
		TS_ASSERT_EQUALS(al.Name(), "Movement");

		al["Condition"] = 1;
	}

	//Ensure that the internal scope that contains the actual sub-actions is being generated properly and can be accessed
	void TestGetActions(void)
	{
		ActionIf al("Movement");
		TS_ASSERT_DIFFERS(al.Find("Actions"), nullptr);
	}

	//Test that update doesn't break anything
	void TestUpdate(void)
	{
		ActionIf al("Movement");
		WorldState ws;
		TS_ASSERT_THROWS_NOTHING(al.Update(ws));
	}

	//Test that we can adopt action lists into the 'actions' attribute of an entity
	void TestActionInEntity(void)
	{
		ActionIf* al = new ActionIf("Movement");
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

		Action* newAction = Factory<Action>::Create("ActionIf")->As<Action>();
		TS_ASSERT_DIFFERS(newAction, nullptr);
		TS_ASSERT_DIFFERS(newAction->Find("Actions"), nullptr);
		TS_ASSERT(newAction->Is("ActionIf"));

		delete newAction;
	}

	//Test that the entity class can successfully create an action list
	void TestEntityCreateAction(void)
	{

		//World sets up factories
		World w;

		//Entity to generate action list with
		Entity e("Ken");
		e.CreateAction("ActionIf", "Movement");
		Scope* a = e.Actions()->Find("Movement")->Get<Scope*>();
		TS_ASSERT_DIFFERS(a, nullptr);
		TS_ASSERT(a->Is("ActionIf"));
		TS_ASSERT_EQUALS(a->As<Action>()->Name(), "Movement");
	}


	void TestActionIf(void)
	{
		ActionIf* al = new ActionIf("If");
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
		XMLParseHelperIf p;
		XMLParseHelperTable pt;
		m.AddHelper(&p);
		m.AddHelper(&pe);
		m.AddHelper(&pu);
		m.AddHelper(&pt);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string =		"<world name=\"Earth\">"
								"<sector name=\"Florida\">"
									"<entity class=\"Entity\" name=\"Ken\">"
										"<integer name =\"ChangeValue\">0</integer>"
										"<integer name =\"Condition\">1</integer>"
										"<action name=\"If\" class=\"ActionIf\" type=\"variable\" condition=\"Condition\">"
											"<action name=\"Then\" class=\"ActionList\">"
												"<action name=\"TestThen\" class=\"ActionExpression\">"
													"this.ChangeValue = 1234"
												"</action>"
											"</action>"
											"<action name=\"Else\" class=\"ActionList\">"
												"<action name=\"TestElse\" class=\"ActionExpression\">"
													"this.ChangeValue = 5678"
												"</action>"
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
		ActionList* actionListIf = Ken->Actions()->Find("If")->Get<Scope*>()->As<ActionList>();
		ActionList* actionThen = actionListIf->Actions()->Find("Then")->Get<Scope*>()->As<ActionList>();
		ActionList* actionElse = actionListIf->Actions()->Find("Else")->Get<Scope*>()->As<ActionList>();

		TS_ASSERT_EQUALS((*actionListIf).Name(), "If");
		TS_ASSERT_EQUALS((*actionThen).Name(), "Then");
		TS_ASSERT_EQUALS((*actionElse).Name(), "Else");

		std::cout << Ken->Find("ChangeValue")->Get<int>() << std::endl;
		WorldState ws;
		w.Update(ws);
		// Because 'condition' is set to '1', ChangeValue is evaluated to 1234
		std::cout << Ken->Find("ChangeValue")->Get<int>() << std::endl;
		actionListIf->Find("Condition")->Set(0);
		w.Update(ws);
		// Because 'condition' is set to '0', ChangeValue is evaluated to 5678
		std::cout << Ken->Find("ChangeValue")->Get<int>() << std::endl;
		actionListIf->Find("Condition")->Set(1);
		w.Update(ws);
		// Because 'condition' is set to '1', ChangeValue is evaluated to 5678 once again
		std::cout << Ken->Find("ChangeValue")->Get<int>() << std::endl;
	}


private:
	_CrtMemState startSnapshot;
};