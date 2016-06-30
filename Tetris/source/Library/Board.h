#pragma once
#include "Sector.h"
#include "SectorTetromino.h"
#include "BlockEntity.h"
#include <vector>
#include <array>
#include <list>

namespace Library
{
	class Board final : public Library::Sector, public EventSubscriber
	{
		RTTI_DECLARATIONS(Board, Sector)
	public:

		/**
		*Default constructor that initializes all member variables
		*/
		Board();

		/**
		*Default constructor that initializes all member variables with a name for the sector
		*/
		Board(std::string name);

		/**
		*Destructor that deallocates all memory allocated by this object
		*/
		virtual ~Board();

		/**
		* Initializes the Board
		*/
		void InitBoard();

		/**
		*Add a block to our block list
		*/
		void AddBlock(BlockEntity* block);

		/**
		*Remove a block to our block list
		*/ 
		void RemoveBlock(BlockEntity* block);

		/**
		Change the player who owns this tetromino
		*/
		void SetPlayer(const std::uint32_t newPlayer);


		/**
		This method checks to see if an entire
		row (10 tetrominoes) is full, and then
		clears it if so
		*/
		void ClearLine();

		/**
		Checks for collision; if returns true, means
		that the tetromino currently is colliding with
		topmost block in a particular column.
		*/
		bool CheckForCollision(SectorTetromino* currentTetromino);

		SectorTetromino* GetCurrentTetromino();
		void SetCurrentTetromino(SectorTetromino* currentTetromino);

		/**
		Send garbage to our opponent
		*/
		void SendGarbage(const std::uint32_t& numGarbage);

		/**
		Setter for our enemy pointer
		*/
		void SetEnemy(Board* enemy);

		/**
		Takes a WorldState reference and updates all of the actions in our action list

		@param curWorldState the current state of the world
		*/
		void Update(WorldState& curWorldState) override;

		/**
		*Called when a player wins the game, shows the end screen with the appropriate player number
		*
		*@param integer representation of the winning player (1 for player 1, 2 for player 2)
		*/
		void WinGame(int player);

		/**
		*Grabs a new block from the tetromino spawner and adds it to this board
		*/
		void RequestBlock();

		/**
		Reinitialize super power stuff
		*/
		void ReinitializePowers();


		/**
		*Called when an event is fired, we check to see if the event is of type
		*/
		void Notify(EventPublisher* publisher) override;

		//Used for super power number 3. Pokes random holes in your board
		void PokeHoles();
		//Static int that stores height
		const static int BOARD_HEIGHT = 22;
		static int sHeight;

		//Static int that stores width
		const static int BOARD_WIDTH = 10;
		static int sWidth;

		//Static int that contains the size of the board array
		static int sBoardSize;

		//Static float that stores initial speed
		static float sInitialSpeed;

		

	private:

		void RenderPowerUpUI(WorldState& curWorldState);

		bool mLock;
		int32_t mPlayer;
		// array of 10 vectors with capacity 22,
		// representing the 10 columns and 22 rows
		// - initialized with all nullptr
		BlockEntity* mBlocks[BOARD_HEIGHT][BOARD_WIDTH];

		int mRowYValues[BOARD_HEIGHT];
		int mColXValues[BOARD_WIDTH];

		int mRowCount[BOARD_HEIGHT];

		float mElapsedTime;
		float mGravityTimeThreshold;

		std::vector<int> mNextClear;

		SectorTetromino* mCurrentTetromino;

		/**
		Pointer to the other player's board
		Used for sending garbage
		*/
		Board* mEnemy;

		std::list<int> mGarbageQueue;

		static int sGarbageCount;
		static int sBlocksInBoard;

		//Used to check to see if we have already been notified of an event this frame
		bool mWasNotified;

		//Check to see if our opponent has activated super power 3 to add holes to our board
		bool mToBeHoled;

		//Used to check if our super powers have been used up yet
		bool mPower1Used;
		bool mPower2Used;
		bool mPower3Used;
		bool mPower4Used;

		//Keep track of the top most row that is filled
		int mTopMostRowIndex;

		void UpdateTopMostRow();
		void PerformPowerupOne();
		sf::Vector2f mPlayer1PowerupPosition;
		sf::Vector2f mPlayer2PowerupPosition;
		sf::Vector2f mPowerupOffset;
	};
}
