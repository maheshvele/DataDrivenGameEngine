#include "pch.h"
#include "TetrominoSpawner.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include <time.h>
#include "World.h"

//TODO: add const values for spawn points of tetris blocks

namespace Library
{

	RTTI_DEFINITIONS(TetrominoSpawner)

	/**
	Initialize static members
	*/
	Board* TetrominoSpawner:: player1Board = nullptr;
	Board* TetrominoSpawner:: player2Board = nullptr;


	/**
	Constructor
	*/
	TetrominoSpawner::TetrominoSpawner() :
			Reaction(""), numSpawned(0)
	{
		//Subscribe to event message attributed
		Event<EventMessageAttributed>::Subscribe(this);

		/* initialize random seed: */
		srand((unsigned int)time(NULL));
	}

	/**
	Named constructor
	*/
	TetrominoSpawner::TetrominoSpawner(const std::string& name) :
		Reaction(name),  numSpawned(0)
	{
		//Subscribe to event message attributed
		Event<EventMessageAttributed>::Subscribe(this);

		/* initialize random seed: */
		srand((unsigned int)time(NULL));
	}

	/**
	Destructor
	*/
	TetrominoSpawner::~TetrominoSpawner()
	{
		while (tetrominoBases.size() > 0)
		{
			delete tetrominoBases.back();
			tetrominoBases.pop_back();
		}

		while (currentQueue.size() > 0)
		{
			delete currentQueue.back();
			currentQueue.pop_back();
		}


		//Unsubscribe to event message attributed
		Event<EventMessageAttributed>::Unsubscribe(this);

	}

	/**
	Give away a tetromino and generate a new one for our queue
	*/
	void TetrominoSpawner::GiveTetromino(std::uint32_t player)
	{
		float spawnX = BASE_X;
		float spawnY = BASE_Y;

		if (player == 1 && player1Board != nullptr)
		{
			player1Board->SetCurrentTetromino(currentQueue.back());
			spawnX += BlockEntity::p1LeftBound;
			spawnX += (BlockEntity::p1RightBound - BlockEntity::p1LeftBound) / 2;
		}
		else if (player == 2 && player2Board != nullptr)
		{
			player2Board->SetCurrentTetromino(currentQueue.back());
			spawnX += BlockEntity::p2LeftBound;
			spawnX += (BlockEntity::p2RightBound - BlockEntity::p2LeftBound) / 2;
		}

		currentQueue.back()->SetPlayer(player);
		currentQueue.back()->SetX(spawnX);
		currentQueue.back()->SetY(spawnY);
		currentQueue.pop_back();
		currentQueue.insert(currentQueue.begin(), Spawn());

		for (uint32_t i = 0; i < currentQueue.size(); ++i)
		{
			currentQueue[i]->SetY((currentQueue.size() - i - 1) * Y_OFFSET_FORMULA + Y_OFFSET);
		}
	}

	/**
	Add a tetromino to our list of bases
	*/
	void TetrominoSpawner::AddBase(SectorTetromino* base)
	{
		tetrominoBases.push_back(base);
	}

	/**
	Spawn a random copy of one of the tetrominoes in our base list
	*/
	SectorTetromino* TetrominoSpawner::Spawn()
	{
		int indexToSpawn = rand() % tetrominoBases.size();
		SectorTetromino* st = new SectorTetromino(*(tetrominoBases[indexToSpawn]));

		st->Find("Name")->Get<std::string>() = "Tetromino" + std::to_string(numSpawned);
		++numSpawned;
		
		st->SetX(SPAWN_QUEUE_X);

		if (curWorld != nullptr)
		{
			st->SetWorld(curWorld);
		}
		
		return st;

	}

	/**
	Used for initialization
	*/
	void TetrominoSpawner::Init()
	{
		currentQueue.push_back(Spawn());
		currentQueue.push_back(Spawn());
		currentQueue.push_back(Spawn());

		for (uint32_t i = 0; i < currentQueue.size(); ++i)
		{
			/**
			Sets the Y positions of each tetromino in the queue.			
			*/
			currentQueue[i]->SetY((currentQueue.size() - i - 1) * Y_OFFSET_FORMULA + Y_OFFSET);
		}
	}

	/**
	Look at the front of the queue
	*/
	SectorTetromino* TetrominoSpawner::Peek()
	{
		return currentQueue.back();
	}

	/**
	Getter for the current queue
	*/
	std::vector<SectorTetromino*>* TetrominoSpawner::GetQueue()
	{
		return &currentQueue;
	}

	//Check messages to see if we're giving away a peice when a player needs a new one
	void TetrominoSpawner::Notify(EventPublisher* publisher)
	{
		Event<EventMessageAttributed>* e = publisher->As<Event<EventMessageAttributed>>();
		if (e != nullptr)
		{
			
			const std::string messageType = e->Message().GetSubtype();
			if (messageType == "lockPlayer1")
			{
				if (player1Board != nullptr && player1Board->GetCurrentTetromino() == nullptr)
				{
					GiveTetromino(1);//Give a new tetromino to player 1
				}
			}
			else if (messageType == "lockPlayer2")
			{
				if (player2Board != nullptr && player2Board->GetCurrentTetromino() == nullptr)
				{
					GiveTetromino(2);//Give a new tetromino to player 2
				}
			}
		}
	}

	/**
	*Sets Player's board
	*/
	void TetrominoSpawner::SetBoard(const std::string& player, Board* board)
	{
		if (player == "1")
		{
			player1Board = board;
		}
		else if (player == "2")
		{
			player2Board = board;

		}
	}

	//Set the current world
	void TetrominoSpawner::SetWorld(Scope* world)
	{
		if (world->Is("World"))
		{
			curWorld = world;
		}
	}

}