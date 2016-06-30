#include "pch.h"
#include "XMLParseHelperTetris.h"
#include "SectorTetromino.h"
#include "BlockEntity.h"
#include "TetrominoSpawner.h"
#include "Board.h"

namespace Library
{
	/**
	Default constructor
	*/
	XMLParseHelperTetris::XMLParseHelperTetris()
	{
	}

	/**
	Destructor
	*/
	XMLParseHelperTetris::~XMLParseHelperTetris()
	{
	}

	/**
	Do any set up we need to parse fresh data
	*/
	void XMLParseHelperTetris::Initialize()
	{
	}

	/**
	Handle the element start with the given name in the given hashmap

	@param name the name of the element to handle
	@param attribuets the hashmap containing the element to handle
	@return true if the element was handled, false otherwise
	*/
	bool XMLParseHelperTetris::StartElementHandler(Library::XmlParseMaster::SharedData* data, std::string name, Library::Hashmap<std::string, std::string>& attributes)
	{

		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		//Check  out the data as our specific shared data
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		if (reinterpereted != nullptr)
		{
			if (name == "board")
			{
				//Grab the current world
				World* curWorld = reinterpereted->GetWorld();

				//We MUST have a world to create a sector
				if (curWorld == nullptr)
				{
					return false;
				}

				//We MUST have a name to be contained by the world
				if (!attributes.ContainsKey("name"))
				{
					return false;
				}

				//We also need to have a player to specify which board we are
				if (!attributes.ContainsKey("player"))
				{
					return false;
				}

				//If we've confirmed that we have those, a new board can be created
				Board* newBoard = new Board(attributes.Find("name")->second);
				newBoard->SetWorld(curWorld);
				newBoard->SetPlayer(std::stoi(attributes.Find("player")->second));

				reinterpereted->IncrementDepth();
				reinterpereted->SetSector(newBoard);
				reinterpereted->SetScope(newBoard);
				reinterpereted->PushName(newBoard->Name());
				reinterpereted->PushIndex(0);

				return true;
			}
			else if (name == "SectorTetromino")
			{
				//Grab the current world
				World* curWorld = reinterpereted->GetWorld();

				//We MUST have a world to create a sector
				if (curWorld == nullptr)
				{
					return false;
				}

				//We MUST have a name to be contained by the world
				if (!attributes.ContainsKey("name"))
				{
					return false;
				}


				//Check to see if we're a prototype for a spawner instead of an actual entity
				Action* curAction = reinterpereted->GetAction();
				if (curAction != nullptr && curAction->Is("TetrominoSpawner"))
				{

					SectorTetromino* newTetromino = new SectorTetromino(attributes.Find("name")->second);
					curAction->As<TetrominoSpawner>()->AddBase(newTetromino);

					reinterpereted->IncrementDepth();
					reinterpereted->SetSector(newTetromino);
					reinterpereted->SetScope(newTetromino);
					reinterpereted->PushName(newTetromino->Name());
					reinterpereted->PushIndex(0);

					return true;
				}
				else
				{
					//Otherwise, make the tetromino as normal
					SectorTetromino* newTetromino = new SectorTetromino(attributes.Find("name")->second);
					newTetromino->SetWorld(curWorld);

					reinterpereted->IncrementDepth();
					reinterpereted->SetSector(newTetromino);
					reinterpereted->SetScope(newTetromino);
					reinterpereted->PushName(newTetromino->Name());
					reinterpereted->PushIndex(0);
				}

				return true;
			}
			else if (name == "BlockEntity")//Parse individual blocks
			{
				//Grab the current world
				World* curWorld = reinterpereted->GetWorld();

				//We MUST have a world to create a sector
				if (curWorld == nullptr)
				{
					return false;
				}

				//Check to make sure that we're inside a sector tetromino
				//Blocks are only legal in sector tetromino
				Sector* curSector = reinterpereted->GetSector();
				if (!curSector->Is("SectorTetromino"))
				{
					return false;
				}

				//We MUST have a name to be contained by the world
				if (!attributes.ContainsKey("name"))
				{
					return false;
				}
				
				//Create a new block and add it to our sectorTetromino
				BlockEntity* newBlock = new BlockEntity(attributes.Find("name")->second, 0);
				newBlock->SetSector(curSector);

				reinterpereted->IncrementDepth();
				reinterpereted->SetEntity(newBlock);
				reinterpereted->SetScope(newBlock);
				reinterpereted->PushName(newBlock->Name());
				reinterpereted->PushIndex(0);
				newBlock->SetPosition(-300.f, -300.f);

				return true;
				
			}
			else if (name == "TetrominoSpawner")//Spawner
			{
				//We need a world to set to our current world to have a tetromino spawner
				World* curWorld = reinterpereted->GetWorld();
				
				if (curWorld == nullptr)
				{
					return false;
				}

				//Grab the current entity
				//We need one to contain us
				Entity* curEntity = reinterpereted->GetEntity();

				if (curEntity == nullptr)
				{
					return false;
				}

				//We MUST have a name
				if (!attributes.ContainsKey("name"))
				{
					return false;
				}

				//We must have two boards defined that we can set as our player1 and player2 boards
				if (!attributes.ContainsKey("board1"))
				{
					return false;
				}

				if (!attributes.ContainsKey("board2"))
				{
					return false;
				}

				//Make sure both boards exist and are also boards 
				Scope* b1 = reinterpereted->GetWorld()->Sectors()->Find(attributes.Find("board1")->second)->Get<Scope*>();
				Scope* b2 = reinterpereted->GetWorld()->Sectors()->Find(attributes.Find("board2")->second)->Get<Scope*>();

				if (b1 == nullptr || b2 == nullptr)
				{
					return false;
				}
				
				//Grab both the boards for initialization
				Board* board1 = b1->As<Board>();
				Board* board2 = b2->As<Board>();

				if (board1 == nullptr || board2 == nullptr)
				{
					return false;
				}

				board1->SetEnemy(board2);
				board2->SetEnemy(board1);

				//Create a new tetrominospawner
				TetrominoSpawner* newSpawn = new TetrominoSpawner(attributes.Find("name")->second);
				newSpawn->SetEntity(curEntity);
				newSpawn->SetWorld(curWorld);
				newSpawn->SetBoard("1", board1);
				newSpawn->SetBoard("2", board2);
				

				reinterpereted->IncrementDepth();
				reinterpereted->SetAction(newSpawn);
				reinterpereted->SetScope(newSpawn);
				reinterpereted->PushName(newSpawn->Name());
				reinterpereted->PushIndex(0);
			}
		}
		return false;
	}

	/**
	Handle the element end with the given name in the given hashmap

	@param name the name of the element to handle
	@return true if the element was handled, false otherwise
	*/
	bool XMLParseHelperTetris::EndElementHandler(Library::XmlParseMaster::SharedData* data, std::string name)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		//Check  out the data as our specific shared data
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();


		if (reinterpereted != nullptr)
		{
			if (name == "board" || name == "SectorTetromino" || name == "UI")
			{
				reinterpereted->DecrementDepth();
				reinterpereted->SetSector(nullptr);
				reinterpereted->SetScope(nullptr);
				reinterpereted->PopName();
				reinterpereted->PopIndex();

				return true;
			}
			else if (name == "BlockEntity")
			{
				reinterpereted->DecrementDepth();
				reinterpereted->SetEntity(nullptr);
				reinterpereted->SetScope(nullptr);
				reinterpereted->PopName();
				reinterpereted->PopIndex();

				return true;
			}
			else if (name == "TetrominoSpawner")
			{
				TetrominoSpawner* curSpawner = reinterpereted->GetAction()->As<TetrominoSpawner>();
				if (curSpawner != nullptr)
				{
					curSpawner->Init();
				}
				else
				{
					return false;
				}

				reinterpereted->DecrementDepth();
				reinterpereted->SetAction(nullptr);
				reinterpereted->SetScope(nullptr);
				reinterpereted->PopName();
				reinterpereted->PopIndex();

				return true;
			}
		}

		return false;
	}

	/**
	Given a string buffer of character data and an integer length, attempt to handle the character data

	@param data the string data to be handled
	@param length the number of characters in data
	@return true if the elemnt was handled, false otherwise
	*/
	bool XMLParseHelperTetris::CharDataHandler(Library::XmlParseMaster::SharedData* data, std::string charData, std::uint32_t length)
	{
		if (!data)
		{
			throw std::exception("Shared data is null");
		}

		//Check  out the data as our specific shared data
		SharedDataWorld* reinterpereted = data->As<SharedDataWorld>();
		if (reinterpereted != nullptr)
		{
			//At the moment, we don't want to handle any char data.
		}
		return false;
	}

	/**
	Duplicate this helper. A 'virtual constructor'. Allocates new memory on the heap that must be deleted.

	@return a newly allocated XMLParseHelperUniverse
	*/
	XMLParseHelperTetris* XMLParseHelperTetris::Clone()
	{
		return new XMLParseHelperTetris();
	}

}