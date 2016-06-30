#include <cxxtest/TestSuite.h>
#include "XMLParseHelperUniverse.h"
#include "XMLParseHelperExpression.h"

using namespace Library;

class ActionParseTestSuite : public CxxTest::TestSuite
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

	//Parse some xml that gives us a single, empty action list
	void TestParseActionList(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"Movement\" class=\"ActionList\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Our world (Earth) should now contain one sector (Florida) that contains one  entity (Ken) which knows one actionList (movement)
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 1);
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);
		TS_ASSERT_EQUALS(Florida->Name(), "Florida");
		
		TS_ASSERT_DIFFERS(Florida->Entities()->Find("Ken"), nullptr);
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_EQUALS(Ken->Name(), "Ken");
		
		TS_ASSERT_DIFFERS(Ken->Actions()->Find("Movement"), nullptr);
		ActionList* Movement = Ken->Actions()->Find("Movement")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_EQUALS(Movement->Name(), "Movement");
		TS_ASSERT_DIFFERS(Movement->Actions(), nullptr);
		TS_ASSERT_EQUALS(Movement->Actions()->Size(), 0);
	}

	//Parse an actionlist that contains actions. For now this will just be a nested empty actionlist.
	void TestParseNestedActionList(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"Movement\" class=\"ActionList\">"
										"<action name=\"Acrobatics\" class=\"ActionList\">"
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

		ActionList* Movement = Ken->Actions()->Find("Movement")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(Movement, nullptr);

		ActionList* Acrobatics = Movement->Actions()->Find("Acrobatics")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(Acrobatics, nullptr);
		TS_ASSERT_EQUALS(Acrobatics->Name(), "Acrobatics");
		TS_ASSERT_DIFFERS(Acrobatics->Actions(), nullptr);
		TS_ASSERT_EQUALS(Acrobatics->Actions()->Size(), 0);
	}

	//Test parsing ActionCreateAction
	//Ensure that the parsed and created action can be updated and used
	void TestActionCreateActionParse(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"ListCreator\" class=\"ActionCreateAction\" prototype=\"ActionList\" creationName=\"CreatedList\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		
		//At this point, the entity Ken should contain 1 action. This action should be of type ActionCreateAction, with the parameters prototype = ActionList and creationName = CreatedList and the name ListCreator
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 1);
		ActionCreateAction* listCreator = Ken->Actions()->Find("ListCreator")->Get<Scope*>()->As<ActionCreateAction>();
		TS_ASSERT_DIFFERS(nullptr, listCreator);
		TS_ASSERT_EQUALS(listCreator->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(listCreator->GetContainer(), Ken);
		TS_ASSERT_EQUALS(listCreator->Name(), "ListCreator");
		TS_ASSERT_EQUALS(listCreator->GetPrototypeName(), "ActionList");
		TS_ASSERT_EQUALS(listCreator->GetCreationName(), "CreatedList");

		WorldState ws;
		w.Update(ws); //This update should iterate through our one sector, which iterates through our one entity, which iterates through our one action, and executes that action

		//Once our listCreator hits its update, it should create a new empty ActionList with the name CreatedList in the Actions subscope of the Ken entity
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 2);
		TS_ASSERT_DIFFERS(Ken->Actions()->Find("CreatedList"), nullptr);
		ActionList* createdList = Ken->Actions()->Find("CreatedList")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(createdList, nullptr);
		TS_ASSERT_EQUALS(createdList->Name(), "CreatedList");
	}

	//Test parsing ActionDestroyAction
	//Ensure that the parsed and created action can be updated and used
	void TestActionDestroyActionParse(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		m.AddHelper(&p);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"Destroyer\" class=\"ActionDestroyAction\" target=\"NewList\">"
									"</action>"
									"<action name=\"NewList\" class=\"ActionList\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		//At this point, the entity Ken should contain 2 actions. The first is a destroyer, which has the second listed as its target
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 2);
		ActionDestroyAction* destroyer = Ken->Actions()->Find("Destroyer")->Get<Scope*>()->As<ActionDestroyAction>();
		TS_ASSERT_DIFFERS(nullptr, destroyer);
		TS_ASSERT_EQUALS(destroyer->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(destroyer->GetContainer(), Ken);
		TS_ASSERT_EQUALS(destroyer->Name(), "Destroyer");
		TS_ASSERT_EQUALS(destroyer->GetTargetName(), "NewList");

		WorldState ws;
		w.Update(ws);
		TS_ASSERT_EQUALS(Ken->Actions()->Find("NewList")->Get<Scope*>(), nullptr);

	}

	//Test parsing an empty action expression being contained in an entity
	void TestEmptyActionExpressionInEntity(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		m.AddHelper(&p);
		m.AddHelper(&pe);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"Empty\" class=\"ActionExpression\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));
		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		//At this point, Ken should contain a single action. It should be an actionExpression with no expression defined
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 1);
		ActionExpression* empty = Ken->Actions()->Find("Empty")->Get<Scope*>()->As<ActionExpression>();
		TS_ASSERT_DIFFERS(nullptr, empty);
		TS_ASSERT_EQUALS(empty->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(empty->GetContainer(), Ken);
		TS_ASSERT_EQUALS(empty->Name(), "Empty");
	}

	//Test parsing an empty action expression being contained in an action list
	void TestEmptyActionExpressionInActionList(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		m.AddHelper(&p);
		m.AddHelper(&pe);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"Container\" class=\"ActionList\">"
										"<action name=\"Empty\" class=\"ActionExpression\">"
										"</action>"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		ActionList* container = Ken->Actions()->Find("Container")->Get<Scope*>()->As<ActionList>();

		//At this point, Ken should contain a single action. It should be an actionExpression with no expression defined
		TS_ASSERT_EQUALS(container->Actions()->Size(), 1);
		ActionExpression* empty = container->Actions()->Find("Empty")->Get<Scope*>()->As<ActionExpression>();
		TS_ASSERT_DIFFERS(nullptr, empty);
		TS_ASSERT_EQUALS(empty->GetParent(), container->Actions());
		TS_ASSERT_EQUALS(empty->GetContainer(), container);
		TS_ASSERT_EQUALS(empty->Name(), "Empty");
	}
	
	//Test parsing action expressions containing some integer expressions that mess with variables in the scopes
	void TestIntegerActionExpression(void)
	{
		World w;
		WorldState ws;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		XMLParseHelperTable pt;
		m.AddHelper(&p);
		m.AddHelper(&pe);
		m.AddHelper(&pt);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<integer name = \"Temperature\">96</integer>"
								"<integer name = \"TemperatureTooHot\">0</integer>"
								"<entity class=\"Entity\" name=\"Paul\">"
									"<integer name = \"Y_Position\">10</integer>"
								"</entity>"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<integer name = \"X_Position\">5</integer>"
									"<action name=\"TeleportX\" class=\"ActionExpression\">"
										"this.X_Position = 10 + this.X_Position"
									"</action>"
									"<action name=\"TeleportPaul\" class=\"ActionExpression\">"
										"Paul.Y_Position = Paul.Y_Position - 9"
									"</action>"
									"<action name=\"IsTooHot\" class=\"ActionExpression\">"
										"TemperatureTooHot = Temperature >= 96"
									"</action>"
									"<action name=\"WeatherMagic\" class=\"ActionExpression\">"
										"Temperature = Temperature - 26"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		Entity* Paul = Florida->Entities()->Find("Paul")->Get<Scope*>()->As<Entity>();

		//At this point, Ken should contain some actions actions. 
		//One should be an actionExpression with set to change Ken's  X_Position, increasing it by 10
		//The other should be an actionExpression set to change Paul's Y_Position, decreasing it by 9
		//Next, there is an actionExpression named IsTooHot that sets Florida's 'temperatureTooHot' value to true or false if the temperature is equal to 96
		//The final one changes the temperature, lowering it by 26 degrees from 96, which was obviously too hot, to a brisk 70
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 4);
		ActionExpression* teleportX = Ken->Actions()->Find("TeleportX")->Get<Scope*>()->As<ActionExpression>();
		ActionExpression* teleportPaul = Ken->Actions()->Find("TeleportPaul")->Get<Scope*>()->As<ActionExpression>();
		ActionExpression* isTooHot = Ken->Actions()->Find("IsTooHot")->Get<Scope*>()->As<ActionExpression>();
		ActionExpression* weatherMagic = Ken->Actions()->Find("WeatherMagic")->Get<Scope*>()->As<ActionExpression>();

		//Confirm inital values of the actions
		TS_ASSERT_DIFFERS(nullptr, teleportX);
		TS_ASSERT_EQUALS(teleportX->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(teleportX->GetContainer(), Ken);
		TS_ASSERT_EQUALS(teleportX->Name(), "TeleportX");

		TS_ASSERT_DIFFERS(nullptr, teleportPaul);
		TS_ASSERT_EQUALS(teleportPaul->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(teleportPaul->GetContainer(), Ken);
		TS_ASSERT_EQUALS(teleportPaul->Name(), "TeleportPaul");

		TS_ASSERT_DIFFERS(nullptr, isTooHot);
		TS_ASSERT_EQUALS(isTooHot->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(isTooHot->GetContainer(), Ken);
		TS_ASSERT_EQUALS(isTooHot->Name(), "IsTooHot");

		TS_ASSERT_DIFFERS(nullptr, weatherMagic);
		TS_ASSERT_EQUALS(weatherMagic->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(weatherMagic->GetContainer(), Ken);
		TS_ASSERT_EQUALS(weatherMagic->Name(), "WeatherMagic");

		//grab (Ken.X_Position) so we can check it before and after
		Datum* xPos = Ken->Find("X_Position");
		TS_ASSERT_EQUALS(xPos->Get<int>(), 5);

		//Grab (Paul.Y_position) so we can check it before and after
		Datum* yPos = Paul->Find("Y_Position");
		TS_ASSERT_EQUALS(yPos->Get<int>(), 10);

		//Grab (Temperature) so we can check it before and after
		Datum* temperature = Florida->Find("Temperature");
		TS_ASSERT_EQUALS(temperature->Get<int>(), 96);

		//Grab (TemperatureTooHot) so we can check it before and after
		Datum* tempTooHot = Florida->Find("TemperatureTooHot");
		TS_ASSERT_EQUALS(tempTooHot->Get<int>(), 0);

		//Update, running all the actions
		TS_ASSERT_THROWS_NOTHING(w.Update(ws));
		
		//Check the values updated by the actions
		TS_ASSERT_EQUALS(xPos->Get<int>(), 15);
		TS_ASSERT_EQUALS(yPos->Get<int>(), 1);
		TS_ASSERT_EQUALS(temperature->Get<int>(), 70);
		TS_ASSERT_EQUALS(tempTooHot->Get<int>(), 1);

	}

	//Test parsing action expressions containing various floating point operations
	void TestFloatActionExpression(void)
	{
		World w;
		WorldState ws;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		XMLParseHelperTable pt;
		m.AddHelper(&p);
		m.AddHelper(&pe);
		m.AddHelper(&pt);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<float name = \"Economy\">0.5</float>"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<float name = \"GrowthRate\">0.75</float>"
									"<action name=\"GrowEconomy\" class=\"ActionExpression\">"
										"Economy = Economy + this.GrowthRate"
									"</action>"
									"<action name=\"ResetGrowth\" class=\"ActionExpression\">"
										"this.GrowthRate = 0"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//What we're looking to have after this parse is two actions
		//The first one increases the float 'economy' of florida by the 'growthRate' float of Ken
		//The second sets this 'growthRate' value to zero
		//The expected behavior h ere is that economy will go from 0.5 to 1.25 and then growthRate will go to 0

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 2);
		ActionExpression* growEconomy = Ken->Actions()->Find("GrowEconomy")->Get<Scope*>()->As<ActionExpression>();
		ActionExpression* resetGrowth = Ken->Actions()->Find("ResetGrowth")->Get<Scope*>()->As<ActionExpression>();

		//Confirm init values of actions
		TS_ASSERT_DIFFERS(nullptr, growEconomy);
		TS_ASSERT_EQUALS(growEconomy->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(growEconomy->GetContainer(), Ken);
		TS_ASSERT_EQUALS(growEconomy->Name(), "GrowEconomy");

		TS_ASSERT_DIFFERS(nullptr, resetGrowth);
		TS_ASSERT_EQUALS(resetGrowth->GetParent(), Ken->Actions());
		TS_ASSERT_EQUALS(resetGrowth->GetContainer(), Ken);
		TS_ASSERT_EQUALS(resetGrowth->Name(), "ResetGrowth");

		//Check init values of datums
		Datum* economy = Florida->Find("Economy");
		TS_ASSERT_EQUALS(economy->Get<float>(), 0.5);

		Datum* growth = Ken->Find("GrowthRate");
		TS_ASSERT_EQUALS(growth->Get<float>(), 0.75);

		//Update, running all the actions
		TS_ASSERT_THROWS_NOTHING(w.Update(ws));

		//Check the values updated by the actions
		TS_ASSERT_EQUALS(economy->Get<float>(), 1.25);
		TS_ASSERT_EQUALS(growth->Get<float>(), 0);
	}

	//Test some expressions deeply nested inside multiple action lists
	void TestNestedExpressions(void)
	{
		World w;
		WorldState ws;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		XMLParseHelperTable pt;
		m.AddHelper(&p);
		m.AddHelper(&pe);
		m.AddHelper(&pt);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<float name = \"Economy\">0.5</float>"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<float name = \"GrowthRate\">0.75</float>"
									"<action name=\"Nest1\" class=\"ActionList\">"
										"<action name=\"Nest2\" class=\"ActionList\">"
											"<action name=\"GrowEconomy\" class=\"ActionExpression\">"
												"Economy = Economy + this.GrowthRate"
											"</action>"
											"<action name=\"ResetGrowth\" class=\"ActionExpression\">"
												"this.GrowthRate = 0"
											"</action>"
										"</action>"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//This should turn out similar to the previous test, but it should be buried underneath two nested actionLists
		//Outside of this, it should function the same as before

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_EQUALS(Ken->Actions()->Size(), 1);
		ActionList* nest1 = Ken->Actions()->Find("Nest1")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_EQUALS(nest1->Actions()->Size(), 1);
		ActionList* nest2 = nest1->Actions()->Find("Nest2")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_EQUALS(nest2->Actions()->Size(), 2);

		ActionExpression* growEconomy = nest2->Actions()->Find("GrowEconomy")->Get<Scope*>()->As<ActionExpression>();
		ActionExpression* resetGrowth = nest2->Actions()->Find("ResetGrowth")->Get<Scope*>()->As<ActionExpression>();

		//Confirm init values of actions
		TS_ASSERT_DIFFERS(nullptr, growEconomy);
		TS_ASSERT_EQUALS(growEconomy->GetParent(), nest2->Actions());
		TS_ASSERT_EQUALS(growEconomy->GetContainer(), nest2);
		TS_ASSERT_EQUALS(growEconomy->Name(), "GrowEconomy");

		TS_ASSERT_DIFFERS(nullptr, resetGrowth);
		TS_ASSERT_EQUALS(resetGrowth->GetParent(), nest2->Actions());
		TS_ASSERT_EQUALS(resetGrowth->GetContainer(), nest2);
		TS_ASSERT_EQUALS(resetGrowth->Name(), "ResetGrowth");

		//Check init values of datums
		Datum* economy = Florida->Find("Economy");
		TS_ASSERT_EQUALS(economy->Get<float>(), 0.5);

		Datum* growth = Ken->Find("GrowthRate");
		TS_ASSERT_EQUALS(growth->Get<float>(), 0.75);

		//Update, running all the actions
		TS_ASSERT_THROWS_NOTHING(w.Update(ws));

		//Check the values updated by the actions
		TS_ASSERT_EQUALS(economy->Get<float>(), 1.25);
		TS_ASSERT_EQUALS(growth->Get<float>(), 0);
	}

private:
	_CrtMemState startSnapshot;
};