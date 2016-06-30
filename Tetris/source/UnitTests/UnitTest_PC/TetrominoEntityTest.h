#include <cxxtest/TestSuite.h>
#include "Board.h"
#include "Action.h"
#include "ActionExpression.h"
#include "ReactionAttributed.h"
#include "Factory.h"
#include "XMLParseHelperTetris.h"
#include "World.h"
#include "SectorTetromino.h"
#include "XMLParseHelperExpression.h"
#include "XMLParseHelperUniverse.h"
#include "BlockEntity.h"


using namespace Library;

class TetrominoEntityTest : public CxxTest::TestSuite
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


	//Test a parse of sector tetromino with the tetris parse helper
	void TestParse(void)
	{
		World w;
		WorldState ws;
		SharedDataWorld sdw(&w);
		XmlParseMaster m(&sdw);
		XMLParseHelperUniverse p;
		XMLParseHelperTetris pht;
		XMLParseHelperTable pt;
		m.AddHelper(&p);
		m.AddHelper(&pht);
		m.AddHelper(&pt);

		TS_ASSERT_EQUALS(w.Sectors()->Size(), 0);

		char* string = "<world name=\"Earth\">"
							"<float name=\"Gravity\">1.0</float>"
							"<SectorTetromino name=\"JBlock\">"
								"<float name=\"X\">10.0</float>"//Initial x value
								"<float name=\"Y\">20.0</float>"//Initial y value
								"<float name=\"Width\">32.0</float>"//Initial width
								"<float name=\"Height\">32.0</float>"//Initial height
								"<BlockEntity name=\"block0\" class=\"Entity\">" 
									"<integer name = \"value\" index=\"0\">0</integer>"               
									"<integer name = \"value\" index=\"1\">1</integer>"
									"<integer name = \"value\" index=\"2\">1</integer>"
									"<integer name = \"value\" index=\"3\">0</integer>"                            
								"</BlockEntity>"
							"</SectorTetromino>"
						"</world>";
		int length = strlen(string);

		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));
		
		//Grab the sector tetromino
		Sector* s = w.Sectors()->Find("JBlock")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(s, nullptr);
		TS_ASSERT(s->Is("SectorTetromino"));

		SectorTetromino* st = s->As<SectorTetromino>();

		//Check the state of the player value in the  sectorTetromino object
		//We expect it to be uninitialized at this time (set to zero)
		TS_ASSERT_EQUALS(st->Find("Player")->Get<int>(), 0);

		//Check the state of the x value (expected to be 10.0)
		TS_ASSERT_EQUALS(st->GetX(), 10.0f);

		//Check the state of the y value (expected to be 20)
		TS_ASSERT_EQUALS(st->GetY(), 20.0f);

		//Check the state of the width (expected to be 32)
		TS_ASSERT_EQUALS(st->Find("Width")->Get<float>(), 32.0f);

		//Check the state of the height (expected to be 32)
		TS_ASSERT_EQUALS(st->Find("Height")->Get<float>(), 32.0f);


		//Grab the single block entity in the sector
		BlockEntity* block = s->Entities()->Find("block0")->Get<Scope*>()->As<BlockEntity>();
		TS_ASSERT_DIFFERS(block, nullptr);

		//Ensure that we have a state array of the expected size
		Datum* value = block->Find("value");
		TS_ASSERT_EQUALS(value->Size(), 4);

		//Ensure that the state get read in correctly
		TS_ASSERT_EQUALS(value->Get<int>(0), 0);
		TS_ASSERT_EQUALS(value->Get<int>(1), 1);
		TS_ASSERT_EQUALS(value->Get<int>(2), 1);
		TS_ASSERT_EQUALS(value->Get<int>(3), 0);
		
		//Check the player value of the block
		//Its expected that it will be 0 (not yet assigned) in this case
		Datum* player = block->Find("Player");
		TS_ASSERT_EQUALS(player->Get<int>(), 0);

		//Check the current state of the single block
		//Should be initialized to the default value of zero
		Datum* state = block->Find("State");
		TS_ASSERT_EQUALS(state->Get<int>(), 0);

	}

		

private:
	_CrtMemState startSnapshot;
};