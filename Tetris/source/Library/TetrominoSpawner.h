#pragma once
#include "SectorTetromino.h"
#include "Board.h"
#include "Reaction.h"

namespace Library
{
	/**
	Constants used to determine the spawn points of the new tetrominoes when they are spawned or added to the preview pool
	*/
	const float BASE_X = -64;
	const float BASE_Y = -32;
	const float SPAWN_QUEUE_X = 448;
	const float Y_OFFSET_FORMULA = 120.0f;
	const float Y_OFFSET = 48.0f;
	
	class TetrominoSpawner : public Reaction
	{
		RTTI_DECLARATIONS(TetrominoSpawner, Reaction)
	public:
		/**
		Constructor
		*/
		TetrominoSpawner();

		/**
		Named constructor
		*/
		explicit TetrominoSpawner(const std::string& name);

		/**
		Destructor
		*/
		virtual ~TetrominoSpawner();

		/**
		Give the current head of our queue to a certain player. Also set its position to that players spawn point and
		generate a new random tetromino that we enqueue

		@param the player to give the tetromino to
		*/
		void GiveTetromino(std::uint32_t player);

		/**
		Add a tetromino to our list of base tetrominoes
		*/
		void AddBase(SectorTetromino* base);

		/**
		Spawn a random copy of a tetromino from our base list
		*/
		SectorTetromino* Spawn();

		/**
		Should react to blocks locking by hitting calling GiveTetromino on the player whose block just locked

		@param publisher the address of a publisher
		*/
		virtual void Notify(EventPublisher* publisher);

		/**
		Getter for the front of the current queue
		*/
		SectorTetromino* Peek();

		/**
		Initialize the first three items in the queue
		*/
		void Init();

		/**
		Getter for the current queue
		*/
		std::vector<SectorTetromino*>* GetQueue();

		/**
		Setter for our current world pointer
		*/
		void SetWorld(Scope* world);

		/**
		*Sets Player's board
		*/
		static void SetBoard(const std::string& player, Board* board);

	private:
		/**Vector of all the bases*/
		std::vector<SectorTetromino*> tetrominoBases;

		/**Queue of the currently held bases in the pool*/
		std::vector<SectorTetromino*> currentQueue;

		/**
		Address of the board object for the first player
		*/
		static Board* player1Board;

		/**
		Address of the board object for the second player
		*/
		static Board* player2Board;

		/**
		Address of the current world
		*/
		Scope* curWorld;

		/**
		Keep track of the number of tetrominoes we have spawned total to ensure that each one has
		a unique name to be inserted into the world with
		*/
		int numSpawned;
	};
}