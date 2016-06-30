#include "pch.h"
#include "Board.h"
#include "BlockEntity.h"
#include "World.h"
#include "WorldState.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include <cmath>
#include "World.h"
#include "TetrominoRender.h"
#include "ActionPlayAudio.h"

namespace Library
{
	RTTI_DEFINITIONS(Board)

	int Board::sHeight = Board::BOARD_HEIGHT;
	int Board::sWidth = Board::BOARD_WIDTH;
	int Board::sBoardSize = Board::sWidth * Board::sHeight;
	float Board::sInitialSpeed = 1.0f;
	int Board::sGarbageCount = 0;
	int Board::sBlocksInBoard = 0;

	/**
	*Default constructor that initializes all member variables
	*/
	Board::Board() :
		Sector(), mCurrentTetromino(nullptr), mNextClear(), mElapsedTime(0), mGravityTimeThreshold(1), mEnemy(nullptr), mGarbageQueue(), 
		mWasNotified(false), mPower1Used(false), mPower2Used(false), mPower3Used(false), mPower4Used(false), mToBeHoled(false), mPowerupOffset(0.f, 100.f)
	{
		InitBoard();

		//Attribute that contains the current speed
		InternalAttribute(Speed, 1, Library::Datum::FLOAT, &sInitialSpeed)

		//Attribute that contains the width
		InternalAttribute(Width, 1, Library::Datum::INTEGER, &sWidth)

		//Attribute that contains the height
		InternalAttribute(Height, 1, Library::Datum::INTEGER, &sHeight)

		//Attribute that contains the current array representing the board itself
		InternalAttribute(Board, sBoardSize, Library::Datum::INTEGER, nullptr)

		InternalAttribute(Player, 1, Datum::DatumType::INTEGER, &mPlayer);

		Event<EventMessageAttributed>::Subscribe(this);

		Populate();
	}

	/**
	*Default constructor that initializes all member variables with a name for the sector
	*/
	Board::Board(std::string name) :
		Sector(name), mCurrentTetromino(nullptr), mNextClear(), mElapsedTime(0), mGravityTimeThreshold(1), mEnemy(nullptr), mGarbageQueue(), 
		mWasNotified(false), mPower1Used(false), mPower2Used(false), mPower3Used(false), mPower4Used(false), mToBeHoled(false), mPowerupOffset(0.f, 100.f)
	{
		InitBoard();

		//Attribute that contains the current speed
		InternalAttribute(Speed, 1, Library::Datum::FLOAT, &sInitialSpeed)

		//Attribute that contains the width
		InternalAttribute(Width, 1, Library::Datum::INTEGER, &sWidth)

		//Attribute that contains the height
		InternalAttribute(Height, 1, Library::Datum::INTEGER, &sHeight)

		//Attribute that contains the current array representing the board itself
		InternalAttribute(Board, sBoardSize, Library::Datum::INTEGER, nullptr)

		InternalAttribute(Player, 1, Datum::DatumType::INTEGER, &mPlayer);

		Event<EventMessageAttributed>::Subscribe(this);

		Populate();
	}

	/**
	*Destructor that deallocates all memory allocated by this object
	*/
	Board::~Board()
	{
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	/**
	Reinitialize powers
	*/
	void Board::ReinitializePowers()
	{
		mPower1Used = false;
		mPower2Used = false;
		mPower3Used = false;
		mPower4Used = false;
	}

	/**
	* Initializes the Board
	*/
	void Board::InitBoard()
	{
		mCurrentTetromino = nullptr;
		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				//clears memory
				if (mBlocks[i][j])
				{
					mBlocks[i][j]->Orphan();
					delete mBlocks[i][j];
				}
				mBlocks[i][j] = nullptr;
			}

			mRowCount[i] = 0;
		}
		BlockEntity::blocks.clear();
		mNextClear.clear();
		mGarbageQueue.clear();
	}

	void Board::Notify(EventPublisher* publisher)
	{
		//If we haven't been notified yet this frame of a keyboard event (we only process one keyboard event per frame)
		if (!mWasNotified && GetWorld()->As<World>()->IsActive())
		{
			World* currentWorld = GetWorld()->As<World>();
			WorldState* currentWorldState = &(currentWorld->GetWorldState());

			if (*(currentWorldState->GetWorld()) == (*currentWorld))
			{
				//See if we can handle the message
				Event<EventMessageAttributed>* message = publisher->As<Event<EventMessageAttributed>>();
				if (message != nullptr)
				{

					//If it's a keyboard pressed event
					if (message->Message().GetSubtype() == "KeyboardRelease")
					{
						//If it's our player's input
						if (message->Message().Find("Player")->Get<int>() == (int)mPlayer)
						{
							//Get which ikey has been pressed and react
							std::string keyPressed = message->Message().Find("Key")->Get<std::string>();

							//If our player is player 1, react to the appropriate keys
							if (mPlayer == 1)
							{
								//Power 1 player 1
								if (keyPressed == "1")
								{
									if (!mPower1Used)
									{
										mPower1Used = true;
										std::cout << "Player 1 pressed 1" << std::endl;
										PerformPowerupOne();
									}
									mWasNotified = true;
								}

								//Power 2 player 1
								if (keyPressed == "2")
								{
									if (!mPower2Used)
									{
										mPower2Used = true;
										std::cout << "Player 1 pressed 2" << std::endl;
										World* currentWorld = GetWorld()->As<World>();
										(*currentWorld)["HideUIPlayer2"] = 1;
										Library::CreateAudioEvent("Splat", GetWorld()->As<World>());
									}
									mWasNotified = true;
								}

								//Power 3 player 1 (random holes)
								if (keyPressed == "3" && !mPower3Used)
								{
									std::cout << "Player 1 pressed 3" << std::endl;
									//mEnemy->PokeHoles();
									mEnemy->mToBeHoled = true;
									mWasNotified = true;
									mPower3Used = true;
								}

								//Power 4 player 1 (Send 4 trash)
								if (keyPressed == "4" && !mPower4Used)
								{
									mGarbageQueue.push_back(4);
									std::cout << "Player 1 pressed 4" << std::endl;
									mPower4Used = true;
									mWasNotified = true;
								}
							}
							else if (mPlayer == 2)
							{
								//Power 1 player 2
								if (keyPressed == "Numpad1")
								{
									if (!mPower1Used)
									{
										std::cout << "Player 2 pressed 1" << std::endl;
										PerformPowerupOne();
										mPower1Used = true;
									}
									mWasNotified = true;
								}

								//Power 2 player 2
								if (keyPressed == "Numpad2")
								{
									if (!mPower2Used)
									{
										mPower2Used = true;
										std::cout << "Player 2 pressed 2" << std::endl;
										World* currentWorld = GetWorld()->As<World>();
										(*currentWorld)["HideUIPlayer1"] = 1;
										Library::CreateAudioEvent("Splat", GetWorld()->As<World>());
									}
									mWasNotified = true;
								}

								//Power 3 player 2 (random holes)
								if (keyPressed == "Numpad3" && !mPower3Used)
								{
									std::cout << "Player 2 pressed 3" << std::endl;
									//mEnemy->PokeHoles();
									mEnemy->mToBeHoled = true;
									mWasNotified = true;
									mPower3Used = true;
								}

								//Power 4 player 2 (Send 4 trash)
								if (keyPressed == "Numpad4" && !mPower4Used)
								{
									mGarbageQueue.push_back(4);
									std::cout << "Player 2 pressed 4" << std::endl;
									mPower4Used = true;
									mWasNotified = true;
								}
							}
						}
					}
				}
			}
		}
	}

	/**
	*Sets the current player number (1 or 2)
	*
	*@param player = which player controls this block (1 or 2)
	*/
	void Board::SetPlayer(const std::uint32_t player)
	{
		mPlayer = player;
		if (mPlayer == 1)
		{
			mColXValues[0] = 96;
			for (int i = 1; i < BOARD_WIDTH; ++i)
			{
				mColXValues[i] = mColXValues[i - 1] + 32;
			}
		}
		else
		{
			mColXValues[0] = 608;
			for (int i = 1; i < BOARD_WIDTH; ++i)
			{
				mColXValues[i] = mColXValues[i - 1] + 32;
			}
		}

		mRowYValues[0] = 704;
		for (int i = 1; i < BOARD_HEIGHT; ++i)
		{
			mRowYValues[i] = mRowYValues[i - 1] - 32;
		}

		Find("Player")->Set((int)player);
	}


	void Board::ClearLine()
	{
		Library::CreateAudioEvent("ClearRow", GetWorld()->As<World>());
		//We spawn n-1 lines of garbage for our opponent, where n is however many
		//lines we cleared
		int numGarbage = mNextClear.size() - 1;

		//In the case that we cleared 4 lines (a tetris) we send all 4 lines of garbage
		if (numGarbage == 3)
		{
			numGarbage++;
		}

		while (mNextClear.size() > 0)
		{
			int curRow = mNextClear.back();

			for (int i = 0; i < BOARD_WIDTH; ++i)
			{
				if (mBlocks[curRow][i])
					delete mBlocks[curRow][i];

				mBlocks[curRow][i] = nullptr;
			}
			mNextClear.pop_back();
			mRowCount[curRow] = 0;

			for (int j = curRow; j < BOARD_HEIGHT - 1; ++j)
			{
				for (int k = 0; k < BOARD_WIDTH; ++k)
				{
					mBlocks[j][k] = mBlocks[j + 1][k];
					if (mBlocks[j][k] != nullptr)
					{
						mBlocks[j][k]->SetPosition((float)mColXValues[k], (float)mRowYValues[j]);
					}
					mBlocks[j + 1][k] = nullptr;
				}
				mRowCount[j] = mRowCount[j + 1];
			}
		}

		//Queue garbage to be send (sends on next tetromino spawn
		mGarbageQueue.push_back(numGarbage);
		//SendGarbage(numGarbage);
	}

	void Board::SendGarbage(const std::uint32_t& numGarbage)
	{
		if (mEnemy != nullptr)
		{
			//Generate the spot in which we will place the hole
			int hole = rand() % BOARD_WIDTH;

			for (std::uint32_t i = 0; i < numGarbage; ++i)
			{
				//Move everything up
				for (int j = BOARD_HEIGHT - 1; j > 0; --j)
				{
					for (int k = 0; k < BOARD_WIDTH; ++k)
					{
						mEnemy->mBlocks[j][k] = mEnemy->mBlocks[j - 1][k];
						if (mEnemy->mBlocks[j][k] != nullptr)
						{
							mEnemy->mBlocks[j][k]->SetPosition((float)mEnemy->mColXValues[k], (float)mEnemy->mRowYValues[j]);
						}
					}
					//Recalculate row count
					mEnemy->mRowCount[j] = mEnemy->mRowCount[j - 1];
				}

				for (int i = 0; i < BOARD_WIDTH; ++i)
				{
					if (i != hole)
					{
						BlockEntity* newBlock = new BlockEntity("garbage" + std::to_string(sGarbageCount), 0);
						++sGarbageCount;
						newBlock->SetSector(mEnemy->As<Scope>());
						newBlock->SetStates(1, 1, 1, 1);
						//Spawn a new row from the bottom
						mEnemy->mBlocks[0][i] = newBlock;
						if (mEnemy->mPlayer == 1)
						{
							(*newBlock)["BlockColor"].Set((std::string)"Blue");
						}
						else
						{
							(*newBlock)["BlockColor"].Set((std::string)"Pink");
						}
						newBlock->SetPosition((float)mEnemy->mColXValues[i], (float)mEnemy->mRowYValues[0]);
					}
					else
					{
						mEnemy->mBlocks[0][i] = nullptr;
					}
				}
				mEnemy->mRowCount[0] = 9;
			}

		}
	}

	/**
	*Called when a player wins the game, shows the end screen with the appropriate player number
	*
	*@param integer representation of the winning player (1 for player 1, 2 for player 2)
	*/
	void Board::WinGame(int player)
	{
		ActionPlayMusic::DestroyMusic();
		Library::CreateAudioEvent("Win", GetWorld()->As<World>());

		if (player == 1)
		{
			(*GetWorld())["Winner"] = 1;
		}
		else
		{
			(*GetWorld())["Winner"] = 2;
		}
	}

	bool Board::CheckForCollision(SectorTetromino* currentTetromino)
	{
		// If the current tetromino is locked, then
		// that means it has collided with something
		// under it (or, under one of the block entities)
		if (currentTetromino != nullptr && currentTetromino->IsLocked())
		{
			std::vector<BlockEntity*>& tetrominoBlocks = currentTetromino->GetBlocks();

			for (auto& block : tetrominoBlocks)
			{
				Datum* values = block->Find("value");
				int curState = values->Get<int>(block->GetState());
				if (curState == 0)
				{
					continue;
				}
				int row = (int)((704 - block->GetY()) / 32);

				if (row > 21)
				{
					if (block->GetPlayer() == 1)
					{
						WinGame(2);
					}
					else
					{
						WinGame(1);

					}
					return false;
				}

				int column = (int)((block->GetX() - mColXValues[0]) / 32);

				// create copies of the BlockEntity's and bring
				// them into the total of the current block entities
				// that occupy the Board
				mBlocks[row][column] = new BlockEntity(*block);
				mBlocks[row][column]->SetPlayer(0);
				mBlocks[row][column]->SetPosition((float)mColXValues[column], (float)mRowYValues[row]);
				mBlocks[row][column]->Find("Name")->Get<std::string>() = "block" + std::to_string(sBlocksInBoard) + "InBoard" + std::to_string(mPlayer);
				mBlocks[row][column]->SetSector(this->As<Scope>());
				++sBlocksInBoard;

				++mRowCount[row];
				if (mRowCount[row] >= 10)
				{
					mNextClear.insert(mNextClear.begin(), row);
					//mNextClear.push_back(row);
				}
			}

			UpdateTopMostRow();

			std::cout << "Now deleting thingy, ... or whatever." << std::endl;
			currentTetromino->Orphan();
			delete currentTetromino;
			mCurrentTetromino = nullptr;

			//Get a new block by enqueueing an event
			RequestBlock();

			std::cout << "Change the output,... to something else then." << std::endl;


			return true;
		}

		return false;
	}

	SectorTetromino* Board::GetCurrentTetromino()
	{
		return mCurrentTetromino;
	}

	void Board::SetCurrentTetromino(SectorTetromino* current)
	{
		//Check to see if we need to be holed this cycle
		if (mToBeHoled)
		{
			PokeHoles();
			mToBeHoled = false;
		}

		while (!mEnemy->mGarbageQueue.empty())
		{
			mEnemy->SendGarbage(mEnemy->mGarbageQueue.front());
			mEnemy->mGarbageQueue.pop_front();
		}
		mCurrentTetromino = current;
	}

	/**
	Setter for enemy
	*/
	void Board::SetEnemy(Board* enemy)
	{
		mEnemy = enemy;
	}

	void Board::Update(WorldState& curWorldState)
	{
		mWasNotified = false;

		mElapsedTime += (float)curWorldState.GetGameTime().ElapsedGameTime();

		if (mCurrentTetromino && CheckForCollision(mCurrentTetromino))
		{
			for (int i = 0; i < BOARD_HEIGHT; ++i)
			{
				std::cout << "|";
				for (int j = 0; j < BOARD_WIDTH; ++j)
				{
					if (mBlocks[i][j] == nullptr)
					{
						std::cout << " ";
					}
					else
					{
						std::cout << "X";
					}
				}
				std::cout << "|" << std::endl;
			}
		}

		if (mNextClear.size() > 0)
		{
			ClearLine();
		}

		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				if (mBlocks[i][j] != nullptr)
				{
					mBlocks[i][j]->Render(curWorldState);
				}
			}
		}

		RenderPowerUpUI(curWorldState);

		// As long as the current Tetromino is maintained, i.e.,
		// received from the PieceSpawner and assigned appropriately,
		// then there will be a piece that can 'lock'.
	}

	void Board::RequestBlock()
	{
		//Enqueue an event to spawn a new block for this player
		EventMessageAttributed message;
		message.SetWorld(GetWorld()->As<World>());
		if (mPlayer == 1)
		{
			message.SetSubtype("lockPlayer1");
		}
		else if (mPlayer == 2)
		{
			message.SetSubtype("lockPlayer2");
		}

		//Make an event out of the message and enqueue it in the world's queue
		std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
		GetWorld()->As<World>()->GetQueue()->Enqueue(event, GetWorld()->As<World>()->GetWorldState().GetGameTime());
	}

	//Used for super power 3 to poke holes in the board
	void Board::PokeHoles()
	{
		for (int i = 0; i < BOARD_HEIGHT; ++i)
		{
			for (int j = 0; j < BOARD_WIDTH; ++j)
			{
				//Generate a random chance to poke a hole (25% chance)
				int rng = rand() % 4;

				if (rng == 0 && mBlocks[i][j] != nullptr)
				{
					delete mBlocks[i][j];
					mBlocks[i][j] = nullptr;
					mRowCount[i]--;
				}
			}
		}
	}

	void Board::UpdateTopMostRow()
	{
		for (int i = BOARD_HEIGHT - 1; i > 0; i--)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				if (mBlocks[i][j])
				{
					mTopMostRowIndex = i;
					std::cout << "Top most row filled is " <<  mTopMostRowIndex << std::endl;
					return;
				}
			}
		}
	}

	void Board::PerformPowerupOne()
	{
		mCurrentTetromino->Orphan();
		delete mCurrentTetromino;
		mCurrentTetromino = nullptr;

		int count = 0;
		Library::CreateAudioEvent("ClearRow", GetWorld()->As<World>());
		for (int i = mTopMostRowIndex; i >= 0; i--)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				if (mBlocks[i][j])
				{
					mRowCount[i]--;
					delete mBlocks[i][j];
					mBlocks[i][j] = nullptr;

				}
			}
			count++;
			if (count == 4)
				break;
		}

		UpdateTopMostRow();
		RequestBlock();
	}
	void Board::RenderPowerUpUI(WorldState& curWorldState)
	{
		sf::Vector2f firstPowerupPosition = sf::Vector2f(35.f, 200.f);

		if (mPlayer == 2)
		{
			firstPowerupPosition += sf::Vector2f(920.f, 0.f);
		}

		if (!mPower1Used)
		{
			TetrominoRender::GetInstance()->RenderOnScreen(*curWorldState.GetWorld()->GetWindow(), TetrominoRender::TextureType::PowerUp1, firstPowerupPosition);
		}

		if (!mPower2Used)
		{
			TetrominoRender::GetInstance()->RenderOnScreen(*curWorldState.GetWorld()->GetWindow(), TetrominoRender::TextureType::PowerUp2, firstPowerupPosition + mPowerupOffset);
		}

		if (!mPower3Used)
		{
			TetrominoRender::GetInstance()->RenderOnScreen(*curWorldState.GetWorld()->GetWindow(), TetrominoRender::TextureType::PowerUp3, firstPowerupPosition + (mPowerupOffset * 2.0f));
		}

		if (!mPower4Used)
		{
			TetrominoRender::GetInstance()->RenderOnScreen(*curWorldState.GetWorld()->GetWindow(), TetrominoRender::TextureType::PowerUp4, firstPowerupPosition + (mPowerupOffset * 3.0f));
		}
	}
}
