#include <cxxtest/TestSuite.h>
#include "World.h"
#include "TetrominoSpawner.h"
#include "BlockEntity.h"
#include "Board.h"
#include "Factory.h"
#include "XMLParseHelperTetris.h"
#include "SectorTetromino.h"
#include "XMLParseHelperExpression.h"
#include "XMLParseHelperUniverse.h"
#include "BlockEntity.h"


using namespace Library;

ConcreteFactory(Scope, BlockEntity);

class TetrominoSpawnTestSuite : public CxxTest::TestSuite
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

	//Make sure everything is functioning before we fill it out via parser
	void TestWithoutParse(void)
	{
		World w;
		std::shared_ptr<BlockEntityFactory> blockfactory(new BlockEntityFactory());

		//Create an IBlock and add it to our bases
		SectorTetromino* s = new SectorTetromino("IBlock", 1);

		std::string instanceName = "block";
		std::string temp;

		s->SetX(320);
		s->SetY(320);

		for (uint32_t i = 0; i < 16; ++i)
		{
			temp = instanceName + std::to_string(i);
			auto entity = s->CreateEntity("BlockEntity", temp);

			switch (i)
			{
			case 1:
			case 13:
				entity->As<BlockEntity>()->SetStates(0, 0, 0, 1);
				break;
			case 2:
			case 14:
				entity->As<BlockEntity>()->SetStates(0, 1, 0, 0);
				break;
			case 4:
			case 7:
				entity->As<BlockEntity>()->SetStates(1, 0, 0, 0);
				break;
			case 5:
				entity->As<BlockEntity>()->SetStates(1, 0, 0, 1);
				break;
			case 6:
				entity->As<BlockEntity>()->SetStates(1, 1, 0, 0);
				break;
			case 8:
			case 11:
				entity->As<BlockEntity>()->SetStates(0, 0, 1, 0);
				break;
			case 9:
				entity->As<BlockEntity>()->SetStates(0, 0, 1, 1);
				break;
			case 10:
				entity->As<BlockEntity>()->SetStates(0, 1, 1, 0);
				break;
			default:
				entity->As<BlockEntity>()->SetStates(0, 0, 0, 0);
				break;
			}
		}

		//Initialize the spawner, spawning 3 tetrominoes in its pool
		TetrominoSpawner t("Spawner");
		t.AddBase(s);
		t.SetWorld(&w);
		t.Init();

		//Ensure that the three blocks we spawn in init were added to the world
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino0"), nullptr);
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino1"), nullptr);
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino2"), nullptr);


		//Check what the next avaliable block is
		SectorTetromino* st = t.Peek();
		TS_ASSERT_DIFFERS(st, nullptr);

		//Make sure that this is actulaly a newly allocated thing and not just the base again
		TS_ASSERT_DIFFERS(st, s);

		//Ensure that our copy has the same blocks that our base created
		for (int i = 0; i < 16; ++i)
		{
			temp = instanceName + std::to_string(i);
			auto entity = st->Entities()->Find(temp);
			TS_ASSERT_DIFFERS(entity, nullptr);
		}

		//Ensure that we can set free st by using the give tetromino method to give it to player 1
		//We can do this by calling its notify with an event of subtype lockPlayer1
		//t.GiveTetromino(1, 0, 0);
		EventMessageAttributed message;
		message.SetSubtype("lockPlayer1");
		
		Event<EventMessageAttributed> e(message);

		e.Deliver();

		//We can do this by checking to see if the current queue of t contains st
		TS_ASSERT_DIFFERS(st, t.Peek());
		TS_ASSERT(std::find(t.GetQueue()->begin(), t.GetQueue()->end(), st) == t.GetQueue()->end());		

		//At this point, we should have also spawned a new guy in the pool named "Tetromino3"
		//Check to ensure that this was added to the world
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino3"), nullptr);

		delete st;
	}

	//Test parsing the spawner
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

		char* string =	"<world name=\"Earth\">"
							"<sector name=\"Florida\">"
								"<entity class=\"Entity\" name=\"SpawnContainer\">"								
									"<TetrominoSpawner name=\"pool\">"
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
									"</TetrominoSpawner>"
								"</entity>"
							"</sector>"
						"</world>";
		int length = strlen(string);
		TS_ASSERT_THROWS_NOTHING(m.Parse(string, length, false));

		//Grab the sector
		Sector* Florida = w.Sectors()->Find("Florida")->Get<Scope*>()->As<Sector>();
		TS_ASSERT_DIFFERS(Florida, nullptr);

		//Grab the spawn container
		Entity* spawnContainer = Florida->Entities()->Find("SpawnContainer")->Get<Scope*>()->As<Entity>();
		TS_ASSERT_DIFFERS(spawnContainer, nullptr);

		//Grab the spawner itself
		TetrominoSpawner* ts = spawnContainer->Actions()->Find("pool")->Get<Scope*>()->As<TetrominoSpawner>();
		TS_ASSERT_DIFFERS(ts, nullptr);

		//Check the next avaliable block
		//Throw out a message that player 1 locked a block and ensure that we can set the next avaliable block free
		SectorTetromino* st = ts->Peek();
		TS_ASSERT_DIFFERS(st, nullptr);

		//Ensure that this tetromino has the one block we set up for it
		auto entity = st->Entities()->Find("block0");
		TS_ASSERT_DIFFERS(entity, nullptr);

		//Make sure that world was given the initial 3 tetromino sectors that spawn in init
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino0"), nullptr);
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino1"), nullptr);
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino2"), nullptr);

		EventMessageAttributed message;
		message.SetSubtype("lockPlayer1");

		Event<EventMessageAttributed> e(message);

		e.Deliver();

		//We can do this by checking to see if the current queue of t contains st
		TS_ASSERT_DIFFERS(st, ts->Peek());
		TS_ASSERT(std::find(ts->GetQueue()->begin(), ts->GetQueue()->end(), st) == ts->GetQueue()->end());

		//At this point, we should have also spawned a new guy in the pool named "Tetromino3"
		//Check to ensure that this was added to the world
		TS_ASSERT_DIFFERS(w.Sectors()->Find("Tetromino3"), nullptr);


		delete st;
	}

private:
	_CrtMemState startSnapshot;
};