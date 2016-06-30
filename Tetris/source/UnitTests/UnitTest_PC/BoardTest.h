#include <cxxtest/TestSuite.h>
#include "Board.cpp"
#include "World.h"
#include "XMLParseHelperTetris.cpp"
#include "XMLParseHelperUniverse.h"
#include "XMLParseHelperExpression.h"

using namespace Library;

class BoardTest : public CxxTest::TestSuite
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


	////Ensure that things initialize fine and we can access our name
	void TestInstantiate(void)
	{
	//	Board b;

	//	//Confirm initial speed
	//	TS_ASSERT_DIFFERS(b.Find("Speed"), nullptr);
	//	TS_ASSERT_EQUALS(b.Find("Speed")->Get<float>(), 1.0f);

	//	//Confirm initial width
	//	TS_ASSERT_DIFFERS(b.Find("Width"), nullptr);
	//	TS_ASSERT_EQUALS(b.Find("Width")->Get<int>(), 10);

	//	//Confirm initial height
	//	TS_ASSERT_DIFFERS(b.Find("Height"), nullptr);
	//	TS_ASSERT_EQUALS(b.Find("Height")->Get<int>(), 22);

	//	//Confirm array size 
	//	TS_ASSERT_DIFFERS(b.Find("Board"), nullptr);
	}

	////Sample of how this would work with containing entities (the pieces)
	//void TestContainer(void)
	//{
	//	//WorldState ws;

	//	//Tetris::Board b;

	//	////E represents a tetromino in this case
	//	//Library::Entity* e = new Library::Entity();

	//	//Datum& yPos = e->Append("yPos");
	//	//yPos.SetType(Datum::FLOAT);
	//	//yPos.Set(2.0f);

	//	//e->SetSector(&b);

	//	////The expression representes the 'gravity' tjhat we could add via XML right now
	//	//Library::ActionExpression* ae = new Library::ActionExpression();
	//	//
	//	//SList<std::string> tokens;
	//	//tokens.PushBack("this.yPos");
	//	//tokens.PushBack("Speed");
	//	//tokens.PushBack("+");
	//	//ae->SetExpression(tokens);
	//	//ae->SetTarget(&yPos);

	//	//ae->SetEntity(e);

	//	//TS_ASSERT_THROWS_NOTHING(b.Update(ws));
	//	//TS_ASSERT_EQUALS(yPos.Get<float>(), 3.0f);
	//	//TS_ASSERT_THROWS_NOTHING(b.Update(ws));
	//	//TS_ASSERT_EQUALS(yPos.Get<float>(), 4.0f);
	//}

	////Sample XML draft
	///*

	//"<world name=\"Tetris\">"
	//	"<board name=\"Player1\">"
	//		"<entity class=\"Tetromnio\" name=\"CurPiece\">"
	//			"<action name=\"ApplyGravity\" class=\"ActionExpression\">"
	//				"this.yPos = this.yPos + Speed"
	//			"</action>"
	//		</entity>
	//	"</board>"
	//"</world>";

	//*/

	////Test out parsing the board object
	//void TestParse(void)
	//{
	//	TS_ASSERT(true);
	//	World w;
	//	WorldState ws;
	//	SharedDataWorld sdw(&w);
	//	XmlParseMaster m(&sdw);
	//	XMLParseHelperUniverse p;
	//	XMLParseHelperTetris pht;
	//	XMLParseHelperTable pt;
	//	XMLParseHelperExpression pe;
	//	m.AddHelper(&p);
	//	m.AddHelper(&pht);
	//	m.AddHelper(&pt);
	//	m.AddHelper(&pe);

	//	TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);

	//	char* string =	"<world name=\"Earth\">"
	//						"<board name=\"Player1\">"	//The variable speed is defined in boards by default
	//							"<entity class=\"Entity\" name=\"CurPiece\">"
	//								"<float name = \"yPos\">0.5</float>"							
	//								"<action name=\"ApplyGravity\" class=\"ActionExpression\">"
	//									"this.yPos = this.yPos + Speed" //Accesses the speed variable of the board
	//								"</action>"
	//							"</entity>"
	//						"</board>"
	//					"</world>";
	//	int length = strlen(string);
	//	TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

	//	Sector* s = w.Sectors()->Find("Player1")->Get<Scope*>()->As<Sector>();
	//	Board* p1 = (Board*)s;

	//	TS_ASSERT_DIFFERS(p1->Find("Speed"), nullptr);
	//	TS_ASSERT_EQUALS(p1->Find("Speed")->Get<float>(), 1.0f);

	//	Entity* e = p1->Entities()->Find("CurPiece")->Get<Scope*>()->As<Entity>();

	//	TS_ASSERT_DIFFERS(e, nullptr);

	//	Datum* yPos = e->Find("yPos");

	//	TS_ASSERT_DIFFERS(yPos, nullptr);
	//	TS_ASSERT_EQUALS(yPos->Get<float>(), 0.5f);

	//	//Update should now increment the yPos of the entity by 1.0f every time
	//	TS_ASSERT_THROWS_NOTHING(w.Update(ws));
	//	TS_ASSERT_EQUALS(yPos->Get<float>(), 1.5f);
	//	TS_ASSERT_THROWS_NOTHING(w.Update(ws));
	//	TS_ASSERT_EQUALS(yPos->Get<float>(), 2.5f);

	//}

private:
	_CrtMemState startSnapshot;
};