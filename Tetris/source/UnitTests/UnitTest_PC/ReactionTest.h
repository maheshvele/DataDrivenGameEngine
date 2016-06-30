#include <cxxtest/TestSuite.h>
#include "EventMessageAttributed.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"
#include "ActionCreateAction.h"
#include "World.h"
#include "XMLParseHelperUniverse.h"
#include "XMLParseHelperExpression.h"


using namespace Library;

class ReactionTestSuite : public CxxTest::TestSuite
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

	//Test the getters and seters for EventMessageAttributed
	void TestMessageGetSet(void)
	{
		EventMessageAttributed e;
		e.SetSubtype("Keyboard");
		TS_ASSERT_EQUALS(e.GetSubtype(), "Keyboard");

		std::shared_ptr<World> w = std::make_shared<World>();
		e.SetWorld(w.get());
		TS_ASSERT_EQUALS(e.GetWorld(), w.get());
	}

	//Ensure the prescriebd attributes of EventMessageAttributed are being set up as expected
	//The EventMessageAttributed should contain an attribute named "arguments" of type Datum::TABLE
	void TestMessageAttributes(void)
	{
		//At the start, there should be no arguments
		EventMessageAttributed e;
		TS_ASSERT_DIFFERS(e.Find("Arguments"), nullptr);

		//Add an argument and make sure it works as expected
		Datum& testDatum = e.GetArguments()->Append("TestArg");
		testDatum.SetType(Datum::INTEGER);
		testDatum.Set(33);
		TS_ASSERT_DIFFERS(e.GetArguments()->Find("TestArg"), nullptr);
		TS_ASSERT_EQUALS(e.GetArguments()->Find("TestArg")->Get<int>(), 33);
	}

	//Test that ReactionAttributed subscribes to EventMEssageAttributed and
	//that its notify is producing the expected output
	void TestReactionAttributed(void)
	{		
		//Set up our message
		EventMessageAttributed e;
		e.SetSubtype("Keyboard");
		Scope* newArgument = new Scope(10);
		Datum& testDatum = newArgument->Append("Test");
		testDatum.SetType(Datum::INTEGER);
		testDatum.Set(33);
		e.GetArguments()->Adopt(newArgument, "TestArg", 0);//Using a table datum to check that nested scope stuff interacts as expected

		//Initialize world flags and factories
		WorldState ws;
		std::shared_ptr<World> w = std::make_shared<World>();
		w->SetWorldState(ws);
		e.SetWorld(w.get());

		//Set up an event with our message
		Event<EventMessageAttributed> eventToFire(e);

		//Set up the ReactionAttributed itself
		std::string subType = "Keyboard";
		ReactionAttributed r("ReactWithCreate", &subType);

		//Ensure that r's attributes got set up correctly
		TS_ASSERT_EQUALS(r.Name(), "ReactWithCreate");//Check name
		TS_ASSERT_EQUALS(r.GetSubtype(), "Keyboard");//Check subtype
		TS_ASSERT_DIFFERS(r.Actions(), nullptr);//Check to make sure we have an actions list

		//Add a new ActionCreateAction to r's action list
		ActionCreateAction* rCreated = r.CreateAction("ActionCreateAction", "rCreated")->As<ActionCreateAction>();
		TS_ASSERT_DIFFERS(rCreated, nullptr);
		TS_ASSERT_EQUALS(rCreated->Name(), "rCreated");
		rCreated->SetPrototypeName("ActionList");
		rCreated->SetCreationName("NewList");
		TS_ASSERT_EQUALS(rCreated->GetPrototypeName(), "ActionList");
		TS_ASSERT_EQUALS(rCreated->GetCreationName(), "NewList");
	
		//Fire the event
		eventToFire.Deliver();

		//Our expected result is that r should now contain a coupy of e's arguments
		//It should have also fired off its EventList::Update, which fires rCreated
		//As such, rCreated should have made a new empty ActionList in r's actions named "NewList"

		Datum* cachedArgs = r.Find("Arguments");//Ensure that we have an argument list
		TS_ASSERT_DIFFERS(cachedArgs, nullptr);

		////Ensure that we have a copy of newArgument under the name TestArg
		TS_ASSERT_DIFFERS(cachedArgs->Get<Scope*>()->Find("TestArg"), nullptr);
		
		//Make sure a new copy was made
	
		//Different addresses
		TS_ASSERT_DIFFERS(cachedArgs->Get<Scope*>(), e.GetArguments());

		TS_ASSERT_DIFFERS(cachedArgs->Get<Scope*>()->Find("TestArg")->Get<Scope*>()->Find("Test"), nullptr);

		//Same contents
		TS_ASSERT_EQUALS(cachedArgs->Get<Scope*>()->Find("TestArg")->Get<Scope*>()->Find("Test")->Get<int>(), e.GetArguments()->Find("TestArg")->Get<Scope*>()->Find("Test")->Get<int>());

		//Double check the value
		TS_ASSERT_EQUALS(cachedArgs->Get<Scope*>()->Find("TestArg")->Get<Scope*>()->Find("Test")->Get<int>(), 33);

		//Test that a 'NewList' was successfully created by the actionCreateAction
		TS_ASSERT_DIFFERS(r.Actions()->Find("NewList"), nullptr);
		TS_ASSERT_EQUALS(r.Actions()->Find("NewList")->Size(), 1);

		ActionList* actionCreated = r.Actions()->Find("NewList")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(actionCreated, nullptr);
		TS_ASSERT_EQUALS(actionCreated->GetContainer(), &r);
	}

	//Test all of the different constructors of ActionEvent
	//Also test getters and setters
	void TestActionEventInstantiation(void)
	{
		EventQueue e;

		//Default constructor
		ActionEvent defaultConstructed;
		TS_ASSERT_DIFFERS(defaultConstructed.Find("Name"), nullptr);
		TS_ASSERT_EQUALS(defaultConstructed.Name(), (""));
		TS_ASSERT_DIFFERS(defaultConstructed.Find("Subtype"), nullptr);
		TS_ASSERT_EQUALS(defaultConstructed.Find("Subtype")->Get<std::string>() , (""));
		
		//Getters and setters for delay and current queue
		defaultConstructed.SetDelay(1.0f);
		TS_ASSERT_EQUALS(defaultConstructed.GetDelay(),1.0f);

		defaultConstructed.SetQueue(&e);
		TS_ASSERT_EQUALS(defaultConstructed.GetQueue(), &e);

		//Getter and setters for arguments
		TS_ASSERT_DIFFERS(defaultConstructed.GetArguments(), nullptr);
		Datum d;
		d.SetType(Datum::INTEGER);
		d.Set(10);
		defaultConstructed.AddArgument(d, "NewArg");
		TS_ASSERT_DIFFERS(defaultConstructed.GetArguments()->Find("NewArg"), &d);
		TS_ASSERT_EQUALS(10, defaultConstructed.GetArguments()->Find("NewArg")->Get<int>());

		//Name constructor
		ActionEvent named("Named");
		TS_ASSERT_EQUALS(named.Name(), "Named");

		//Name and type constructor
		std::string subtypeString1 = "SubType1";
		std::string subtypeString2 = "SubType2";
		ActionEvent namedAndTyped("NamedAndTyped", &subtypeString1);
		TS_ASSERT_EQUALS(namedAndTyped.Name(), "NamedAndTyped");
		TS_ASSERT_DIFFERS(namedAndTyped.GetSubtype(), subtypeString2);
		TS_ASSERT_EQUALS(namedAndTyped.GetSubtype(), subtypeString1);

		//Name and many types constructor
		std::string multipleTypes[] = { subtypeString1, subtypeString2 };
		ActionEvent multiTyped(std::string("MultiTyped"), multipleTypes, 2);
		TS_ASSERT_EQUALS(multiTyped.Name(), "MultiTyped");
		TS_ASSERT_EQUALS(multiTyped.GetSubtype(0), subtypeString1);
		TS_ASSERT_EQUALS(multiTyped.GetSubtype(1), subtypeString2);
	}

	//Test getters and setters for subtype and arguments
	void TestActionEventSubtypeArgs(void)
	{
		ActionEvent a;
		a.SetSubtype("Keyboard");
		TS_ASSERT_EQUALS(a.GetSubtype(), "Keyboard");

		Datum d;
		d.SetType(Datum::INTEGER);
		d.Set(10);
		a.AddArgument(d, "Arg");
		TS_ASSERT_EQUALS(a.GetArguments()->Find("Arg")->Get<int>(), 10);
	}

	//Test that the update of ActionEvent works as expected
	void TestActionEventUpdate(void)
	{
		//Create an EventQueue
		EventQueue q;

		//Set up a world, worldState, and arguments
		Datum testDatum;// = newArgument->Append("Test");
		testDatum.SetType(Datum::INTEGER);
		testDatum.Set(33);

		WorldState ws;
		std::shared_ptr<World> w = std::make_shared<World>();
		w->SetWorldState(ws);
		
		//Set up a ReactionAttributed
		std::string subType = "Keyboard";
		ReactionAttributed r("ReactWithCreate", &subType);

		//Add a new ActionCreateAction to r's action list
		ActionCreateAction* rCreated = r.CreateAction("ActionCreateAction", "rCreated")->As<ActionCreateAction>();
		rCreated->SetPrototypeName("ActionList");
		rCreated->SetCreationName("NewList");

		//Set up an ActionEvent
		ActionEvent ae("ActionEvent", &subType);
	
		//Arguments
		ae.AddArgument(testDatum, "TestArg");

		//Link to queue
		ae.SetQueue(&q);

		//Update the ActionEvent, queing a new event
		ae.Update(ws);

		//Update the game time
		ws.GetGameTime().SetTotalGameTime(10);

		//Fire the events in the queue
		q.Update(ws.GetGameTime());

		//Confirm that the ReactionAttributed worked the same as before
		Datum* cachedArgs = r.Find("Arguments");//Ensure that we have an argument list
		TS_ASSERT_DIFFERS(cachedArgs, nullptr);

		//Ensure that we have a copy of newArgument under the name TestArg
		TS_ASSERT_DIFFERS(cachedArgs->Get<Scope*>()->Find("TestArg"), nullptr);
		TS_ASSERT_DIFFERS(cachedArgs->Get<Scope*>()->Find("TestArg"), &testDatum);
		TS_ASSERT_EQUALS(cachedArgs->Get<Scope*>()->Find("TestArg")->Get<int>(), 33);

		//Test that a 'NewList' was successfully created
		TS_ASSERT_DIFFERS(r.Actions()->Find("NewList"), nullptr);
		TS_ASSERT_EQUALS(r.Actions()->Find("NewList")->Size(), 1);

		ActionList* actionCreated = r.Actions()->Find("NewList")->Get<Scope*>()->As<ActionList>();
		TS_ASSERT_DIFFERS(actionCreated, nullptr);
		TS_ASSERT_EQUALS(actionCreated->GetContainer(), &r);
	}

	//Test out the behavior that occurs when an actionEvent produces an event with no args
	void TestEmptyActionEventUpdate(void)
	{
		//Create an EventQueue
		EventQueue q;

		WorldState ws;
		std::shared_ptr<World> w = std::make_shared<World>();
		w->SetWorldState(ws);

		//Set up a ReactionAttributed
		std::string subType = "Keyboard";
		ReactionAttributed r("EmptyReact", &subType);

		//Set up an ActionEvent
		ActionEvent ae("ActionEvent", &subType);

		//Link to queue
		ae.SetQueue(&q);

		//Ensure that ae has no arguments
		TS_ASSERT_EQUALS(ae.GetArguments()->Size(), 0);

		//Update the ActionEvent, queing a new event
		ae.Update(ws);

		//Update the game time
		ws.GetGameTime().SetTotalGameTime(10);

		//Fire the events in the queue
		q.Update(ws.GetGameTime());

		//Confirm that the ReactionAttributed didn't have anything copied to it
		Scope* cachedArgs = r.Find("Arguments")->Get<Scope*>();
		TS_ASSERT_DIFFERS(cachedArgs, nullptr);		
		TS_ASSERT_EQUALS(cachedArgs->Size(), 0);
	}

	//Test factories
	void TestFactories(void)
	{
		//Set up world and queue
		World w;
		WorldState ws;
		w.SetWorldState(ws);
		EventQueue eq;
		w.SetQueue(&eq);

		Entity e;
		ReactionAttributed* createdRA = e.CreateAction("ReactionAttributed", "createdReaction")->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(createdRA, nullptr);
		createdRA->AddSubtype("Keyboard");

		ActionEvent* createdAE = e.CreateAction("ActionEvent", "createdActionEvent")->As<ActionEvent>();
		TS_ASSERT_DIFFERS(createdAE, nullptr);

		Datum d;
		d.SetType(Datum::STRING);
		d.Set("Test");
		createdAE->AddArgument(d, "Arg");
		
		//Update should result in a new event being added to eq
		createdAE->Update(ws);

		//Update the time
		ws.GetGameTime().SetTotalGameTime(10.0);

		//EQ firing now should copy test arg into createdRA
		eq.Update(ws.GetGameTime());

		Scope* cachedArgs = createdRA->Find("Arguments")->Get<Scope*>();//Ensure that we have an argument list
		TS_ASSERT_DIFFERS(cachedArgs, nullptr);
		TS_ASSERT_EQUALS(cachedArgs->Find("Arg")->Get<std::string>(), "Test");
	}

	//Test parsing for empty ReactionAttributed and ActionEvent
	void TestParseEmpty(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		WorldState ws;
		w.SetWorldState(ws);
		EventQueue eq;
		w.SetQueue(&eq);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		m.AddHelper(&p);
		m.AddHelper(&pe);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"ReactWithNothing\" class=\"ReactionAttributed\" subtype=\"Keyboard\">"
									"</action>"
									"<action name=\"CreateWithNoArgs\" class=\"ActionEvent\" subtype=\"Keyboard\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		//Make sure nothing broke and we can grab the sector and entity we created
		TS_ASSERT_EQUALS(w.Sectors()->Size(), 1);
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);
		TS_ASSERT_EQUALS(Florida->Name(), "Florida");

		TS_ASSERT_DIFFERS(Florida->Entities()->Find("Ken"), nullptr);
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_EQUALS(Ken->Name(), "Ken");

		//Ensure that the actions created in Ken exist
		ReactionAttributed* r = Ken->Actions()->Find("ReactWithNothing")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(r, nullptr);//Ensure that r exists
		TS_ASSERT_EQUALS(r->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args

		ActionEvent* ae = Ken->Actions()->Find("CreateWithNoArgs")->Get<Scope*>()->As<ActionEvent>();
		TS_ASSERT_DIFFERS(ae, nullptr);//Ensure that ae exists
		TS_ASSERT_EQUALS(ae->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(ae->GetArguments()->Size(), 0);//Ensure that there are no args		
	}

	//Test parsing a ReactionAttributed with multiple subtypes
	void TestMultipleSubtypes(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		WorldState ws;
		w.SetWorldState(ws);
		EventQueue eq;
		w.SetQueue(&eq);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperExpression pe;
		m.AddHelper(&p);
		m.AddHelper(&pe);


		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		char* string = "<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"ReactWithNothing\" class=\"ReactionAttributed\" subtype=\"Keyboard,Mouse,Controller\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();		
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		//Ensure that the actions created in Ken exist
		ReactionAttributed* r = Ken->Actions()->Find("ReactWithNothing")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(r, nullptr);//Ensure that r exists
		TS_ASSERT_EQUALS(r->GetSubtype(), "Keyboard");//Check the first subtype
		TS_ASSERT_EQUALS(r->GetSubtype(1), "Mouse");//Check the second subtype
		TS_ASSERT_EQUALS(r->GetSubtype(2), "Controller");//Check the third subtype
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args
	}

	//Test a parse that fills out the args of the ActionEvent. Run the event, and make sure it enqueues a new event with the correct args
	void TestParseWithArgs(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		WorldState ws;
		w.SetWorldState(ws);
		EventQueue eq;
		w.SetQueue(&eq);
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
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"ReactWithNothing\" class=\"ReactionAttributed\" subtype=\"Keyboard\">"
									"</action>"
									"<action name=\"CreateWithArgs\" class=\"ActionEvent\" subtype=\"Keyboard\">"
										"<integer name = \"Arg\">10</integer>"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		//Get Sector and entity
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		//Ensure that the actions created in Ken exist
		ReactionAttributed* r = Ken->Actions()->Find("ReactWithNothing")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(r, nullptr);//Ensure that r exists
		TS_ASSERT_EQUALS(r->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args

		ActionEvent* ae = Ken->Actions()->Find("CreateWithArgs")->Get<Scope*>()->As<ActionEvent>();
		TS_ASSERT_DIFFERS(ae, nullptr);//Ensure that ae exists
		TS_ASSERT_EQUALS(ae->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(ae->GetArguments()->Size(), 1);//Ensure that there is 1 arg
		TS_ASSERT_DIFFERS(ae->GetArguments()->Find("Arg"), nullptr);//Ensure that the one argument we contain is named Arg 
		TS_ASSERT_EQUALS(ae->GetArguments()->Find("Arg")->Get<int>(), 10);//Ensure it has the interger value of 10

		//Fire off the action event, which should create a new event in eq
		TS_ASSERT_THROWS_NOTHING(ae->Update(ws));
		
		//Update the world time
		ws.GetGameTime().SetTotalGameTime(10.0);

		//Fire off eq, which should copy our single argument into ReactWithNothing
		eq.Update(ws.GetGameTime());

		//Make sure that we have the argument now
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 1);
		TS_ASSERT_DIFFERS(r->Find("Arguments")->Get<Scope*>()->Find("Arg"), nullptr);//Ensure that the one argument we contain is named Arg 
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Find("Arg")->Get<int>(), 10);//Ensure it has the interger value of 10
	}

	//Try filling out the ActionList of a ReactionAttributed via XML
	void TestParseReactionActionList(void)
	{
		//World w;
		//SharedDataWorld sdw(&w);
		//WorldState ws;
		//w.SetWorldState(ws);
		//EventQueue eq;
		//w.SetQueue(&eq);
		//XmlParseMaster m(&sdw);
		//XMLParseHelperUniverse p;
		//XMLParseHelperExpression pe;
		//XMLParseHelperTable pt;
		//m.AddHelper(&p);
		//m.AddHelper(&pe);
		//m.AddHelper(&pt);

		//TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);
		//char* string = "<world name=\"Earth\">"
		//					"<sector name=\"Florida\">"
		//						"<integer name = \"Temperature\">96</integer>"
		//						"<entity class=\"Entity\" name=\"Ken\">"
		//							"<action name=\"ReactWithWeatherMagic\" class=\"ReactionAttributed\" subtype=\"Keyboard\">"				
		//								"<action name=\"WeatherMagic\" class=\"ActionExpression\">"
		//									"Temperature = Temperature - 26"
		//								"</action>"
		//							"</action>"
		//						"</entity>"
		//					"</sector>"
		//				"</world>";
		//int length = strlen(string);
		//TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//TS_ASSERT_EQUALS(sdw.Depth(), 0);

		////Get Sector and entity
		//Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		//Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		////Ensure that the actions created in Ken exist
		//ReactionAttributed* r = Ken->Actions()->Find("ReactWithWeatherMagic")->Get<Scope*>()->As<ReactionAttributed>();
		//TS_ASSERT_DIFFERS(r, nullptr);//Ensure that r exists
		//TS_ASSERT_EQUALS(r->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		//TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args		
		//TS_ASSERT_EQUALS(r->Actions()->Size(), 1);//Ensure that we have a nested action expression

		////Make sure that the action expression is what we expect
		//TS_ASSERT_DIFFERS(r->Actions()->Find("WeatherMagic"), nullptr);
		//ActionExpression* ae = r->Actions()->Find("WeatherMagic")->Get<Scope*>()->As<ActionExpression>();
		//TS_ASSERT_DIFFERS(ae, nullptr);
		//TS_ASSERT_EQUALS(ae->GetExpression().Front(), "Temperature");
		//TS_ASSERT_EQUALS(ae->GetExpression().Back(), "-");
	
		////Double check the value of temperature
		//Datum* temperature = Florida->Find("Temperature");
		//TS_ASSERT_EQUALS(temperature->GetType(), Datum::INTEGER);
		//TS_ASSERT_EQUALS(temperature->Get<int>(), 96);

		////Set up an event that wasn't created via XML so that we can test to ensure it triggers the reaction and updates Temperature as expected
		//EventMessageAttributed ema;
		//ema.SetWorld(&w);
		//ema.SetSubtype("Keyboard");
		//Event<EventMessageAttributed> e(ema);
		//e.Deliver();

		////At this point temperature should have updated to 70
		//TS_ASSERT_EQUALS(temperature->Get<int>(), 70);
	}

	//Test the whole system together
	//The ultimate goal here is to recreate the behavior of the above tests using the XML
	void TestFullSystemParse(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		WorldState ws;
		w.SetWorldState(ws);
		EventQueue eq;
		w.SetQueue(&eq);
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
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"ReactWithWeatherMagic\" class=\"ReactionAttributed\" subtype=\"Keyboard\">"
										"<action name=\"WeatherMagic\" class=\"ActionExpression\">"
										"Temperature = Temperature - 26"
										"</action>"
									"</action>"
									"<action name=\"CreateWithArgs\" class=\"ActionEvent\" subtype=\"Keyboard\">"
										"<integer name = \"Arg\">10</integer>"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		//Get Sector and entity
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		//Ensure that the actions created in Ken exist
		ReactionAttributed* r = Ken->Actions()->Find("ReactWithWeatherMagic")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(r, nullptr);//Ensure that r exists
		TS_ASSERT_EQUALS(r->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args		
		TS_ASSERT_EQUALS(r->Actions()->Size(), 1);//Ensure that we have a nested action expression

		ActionEvent* ae = Ken->Actions()->Find("CreateWithArgs")->Get<Scope*>()->As<ActionEvent>();
		TS_ASSERT_DIFFERS(ae, nullptr);
		TS_ASSERT_EQUALS(ae->GetArguments()->Size(), 1);
		TS_ASSERT_EQUALS(ae->GetArguments()->Find("Arg")->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(ae->GetArguments()->Find("Arg")->Get<int>(), 10);

		//Double check the value of temperature
		Datum* temperature = Florida->Find("Temperature");
		TS_ASSERT_EQUALS(temperature->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(temperature->Get<int>(), 96);

		//Ensure that we have no values in the event queue at this moment
		TS_ASSERT(eq.IsEmpty());

		//This first update should hit the action event, creating a new Event<EventMessageAttributed> in the event queue
		w.Update(ws);

		//Check that the event queue is no longer empty
		TS_ASSERT(!eq.IsEmpty());

		//Update time so that the event will be ready to fire
		ws.GetGameTime().SetTotalGameTime(10.0);

		//This second update should fire off the EventQueue
		w.Update(ws);

		//Ensure that r has a copy of the argument that was in the event now
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Size(), 1);
		TS_ASSERT_EQUALS(r->Find("Arguments")->Get<Scope*>()->Find("Arg")->Get<int>(), 10);

		//At this point temperature should have updated to 70
		TS_ASSERT_EQUALS(temperature->Get<int>(), 70);
	}

	//Test a run with multiple events being created with different subtypes and arguments
	//Also ensure that multiple reactions with different subtypes function correctly
	void TestMultipleReactionsAndEvents(void)
	{
		World w;
		SharedDataWorld sdw(&w);
		WorldState ws;
		w.SetWorldState(ws);
		EventQueue eq;
		w.SetQueue(&eq);
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
								"<integer name = \"Population\">10000</integer>"
								"<integer name = \"Economy\">100</integer>"
								"<entity class=\"Entity\" name=\"Ken\">"
									"<action name=\"ReactWithWeatherMagic\" class=\"ReactionAttributed\" subtype=\"Keyboard\">"
										"<action name=\"WeatherMagic\" class=\"ActionExpression\">"
											"Temperature = Temperature - 26"
										"</action>"
									"</action>"
									"<action name=\"ReactWithEconomyGrowth\" class=\"ReactionAttributed\" subtype=\"Mouse\">"
										"<action name=\"EconomyGrowth\" class=\"ActionExpression\">"
											"Economy = Economy * 10"
										"</action>"
									"</action>"
									"<action name=\"ReactNever\" class=\"ReactionAttributed\" subtype=\"Cellphone\">"
										"<action name=\"NeverHappens\" class=\"ActionExpression\">"
											"Population = 0"
										"</action>"
									"</action>"
									"<action name=\"CreateWithArgs\" class=\"ActionEvent\" subtype=\"Keyboard\">"
										"<integer name = \"Arg\">10</integer>"
									"</action>"
									"<action name=\"CreateWithNoArgs\" class=\"ActionEvent\" subtype=\"Mouse\">"
									"</action>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		TS_ASSERT_EQUALS(sdw.Depth(), 0);

		//Get Sector and entity
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		Entity* Ken = Florida->Entities()->Find("Ken")->Get<Scope*>()->As<Entity>();

		//Ensure that the actions created in Ken exist
		//Check the ReactionAttributeds
		ReactionAttributed* ReactWeather = Ken->Actions()->Find("ReactWithWeatherMagic")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(ReactWeather, nullptr);//Ensure it exists
		TS_ASSERT_EQUALS(ReactWeather->GetSubtype(), "Keyboard");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(ReactWeather->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args		
		TS_ASSERT_EQUALS(ReactWeather->Actions()->Size(), 1);//Ensure that we have a nested action expression

		ReactionAttributed* ReactEconomy = Ken->Actions()->Find("ReactWithEconomyGrowth")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(ReactEconomy, nullptr);//Ensure it exists
		TS_ASSERT_EQUALS(ReactEconomy->GetSubtype(), "Mouse");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(ReactEconomy->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args		
		TS_ASSERT_EQUALS(ReactEconomy->Actions()->Size(), 1);//Ensure that we have a nested action expression

		ReactionAttributed* ReactNever = Ken->Actions()->Find("ReactNever")->Get<Scope*>()->As<ReactionAttributed>();
		TS_ASSERT_DIFFERS(ReactNever, nullptr);//Ensure it exists
		TS_ASSERT_EQUALS(ReactNever->GetSubtype(), "Cellphone");//Ensure that the subtype is what is expected
		TS_ASSERT_EQUALS(ReactNever->Find("Arguments")->Get<Scope*>()->Size(), 0);//Ensure that there are no args		
		TS_ASSERT_EQUALS(ReactNever->Actions()->Size(), 1);//Ensure that we have a nested action expression

		//Check the ActionEvents
		ActionEvent* CreateArgs = Ken->Actions()->Find("CreateWithArgs")->Get<Scope*>()->As<ActionEvent>();
		TS_ASSERT_DIFFERS(CreateArgs, nullptr);
		TS_ASSERT_EQUALS(CreateArgs->GetSubtype(), "Keyboard");
		TS_ASSERT_EQUALS(CreateArgs->GetArguments()->Size(), 1);
		TS_ASSERT_EQUALS(CreateArgs->GetArguments()->Find("Arg")->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(CreateArgs->GetArguments()->Find("Arg")->Get<int>(), 10);

		ActionEvent* CreateNoArgs = Ken->Actions()->Find("CreateWithNoArgs")->Get<Scope*>()->As<ActionEvent>();
		TS_ASSERT_DIFFERS(CreateNoArgs, nullptr);
		TS_ASSERT_EQUALS(CreateNoArgs->GetSubtype(), "Mouse");
		TS_ASSERT_EQUALS(CreateNoArgs->GetArguments()->Size(), 0);

		//Double check the value of temperature, population, and economy
		Datum* temperature = Florida->Find("Temperature");
		TS_ASSERT_EQUALS(temperature->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(temperature->Get<int>(), 96);

		Datum* population = Florida->Find("Population");
		TS_ASSERT_EQUALS(population->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(population->Get<int>(), 10000);

		Datum* economy = Florida->Find("Economy");
		TS_ASSERT_EQUALS(economy->GetType(), Datum::INTEGER);
		TS_ASSERT_EQUALS(economy->Get<int>(), 100);


		//Ensure that we have no values in the event queue at this moment
		TS_ASSERT(eq.IsEmpty());

		//This first update should hit the action events
		//This will create two events in the the event queue
		//The first event will be of subtype "Keyboard" with a single argument (Arg) that has a value of 10
		//The second event will be of subtype "Mouse" with no arguments
		//Note that no event of type "Cellphone" is ever created
		w.Update(ws);

		//Check that the event queue is no longer empty
		TS_ASSERT(!eq.IsEmpty());

		//Update time so that the event will be ready to fire
		ws.GetGameTime().SetTotalGameTime(10.0);

		//This second update should fire off the EventQueue
		w.Update(ws);

		//Ensure that ReactWeather has a copy of the argument that was in the event now
		TS_ASSERT_EQUALS(ReactWeather->Find("Arguments")->Get<Scope*>()->Size(), 1);
		TS_ASSERT_EQUALS(ReactWeather->Find("Arguments")->Get<Scope*>()->Find("Arg")->Get<int>(), 10);

		//Ensure that ReactEconomy and ReactNever still have no arguments
		TS_ASSERT_EQUALS(ReactEconomy->Find("Arguments")->Get<Scope*>()->Size(), 0);
		TS_ASSERT_EQUALS(ReactNever->Find("Arguments")->Get<Scope*>()->Size(), 0);

		//At this point temperature should have updated to 70
		TS_ASSERT_EQUALS(temperature->Get<int>(), 70);

		//Economy should have increased 10 times its original value
		TS_ASSERT_EQUALS(economy->Get<int>(), 1000);

		//Population should not have changed
		TS_ASSERT_EQUALS(population->Get<int>(), 10000);
	}

private:
	_CrtMemState startSnapshot;
};