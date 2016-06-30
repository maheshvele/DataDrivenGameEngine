#include "pch.h"
#include <string>
#include "Board.h"
#include "BlockEntity.h"
#include "SectorTetromino.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "World.h"

using namespace std;
namespace Library
{
	RTTI_DEFINITIONS(SectorTetromino);

	const std::string SectorTetromino::PossibleColors[] = {
		"Green",
		"Blue",
		"Pink",
		"Yellow",
		"Orange",
		"Purple"
	};

	const std::uint32_t SectorTetromino::NumberOfPossibleColors = 6;


	/**
	*Default constructor that initializes all members
	*
	*@param name = the name of the sector attribute
	*@param player = an integer representation of the player number (0 for no player, 1 for player 1, 2 for player 2
	*/
	SectorTetromino::SectorTetromino(const std::string& name, uint32_t player) : Sector(name), mLock(false), mWidth(0), mHeight(0), mBlocks(), mX(0), mY(0), mPlayer(player), mUndoRotate(false), mSFClock(), mRotateCooldown(false), mBlockLock(false), mRotateCooldownAmount(0.5f), mGravityInterval(1.0f)
	{
		ExternalAttribute(Player, Datum::INTEGER, 1, &mPlayer)
		ExternalAttribute(X, Datum::FLOAT, 1, &mX)
		ExternalAttribute(Y, Datum::FLOAT, 1, &mY)
		ExternalAttribute(Width, Datum::FLOAT, 1, &mWidth)
		ExternalAttribute(Height, Datum::FLOAT, 1, &mHeight)
		Populate();
	}

	/**
	*Copy constructor that replicates all members of the rhs to this object
	*
	*@param rhs = the sector to copy
	*/
	SectorTetromino::SectorTetromino(const SectorTetromino& rhs) : 
		Sector(""), mLock(false), mWidth(rhs.mWidth), mHeight(rhs.mHeight), mBlocks(), mX(0), mY(0), mPlayer(rhs.mPlayer), mUndoRotate(false), mPlayRotate(false), mSFClock(), mRotateCooldown(false), mBlockLock(false), mRotateCooldownAmount(0.5f), mGravityInterval(1.0f)
	{
		ExternalAttribute(Player, Datum::INTEGER, 1, &mPlayer)
		ExternalAttribute(X, Datum::FLOAT, 1, &mX)
		ExternalAttribute(Y, Datum::FLOAT, 1, &mY)
		ExternalAttribute(Width, Datum::FLOAT, 1, &mWidth)
		ExternalAttribute(Height, Datum::FLOAT, 1, &mHeight)
		Populate();

		int i = 0;

		//Random color for all blocks in this tetromino
		int indexOfColor = rand() % NumberOfPossibleColors;

		//for every block in the territory
		for (auto& block : rhs.mBlocks)
		{
			//Append a name to the scope
			BlockEntity* newBlock = new BlockEntity(*block);
			newBlock->Find("Name")->Get<std::string>() = "block" + std::to_string(i);
			newBlock->SetSector(this->As<Scope>());

			//Append a color to the scope
			auto& colorDatum = (*newBlock)["BlockColor"];
			colorDatum.SetType(Datum::DatumType::STRING);
			colorDatum = std::string(PossibleColors[indexOfColor]);//pass in color here
			++i;
		}

	}

	/**
	*Enacts gravity on all blocks, for both players after a certain time threshhold, rotates them, locks them, and renders them to the screen
	*
	*@param curWorldState = the state of the world, that contains pointers to the current world, sector, and entity
	*/
	void SectorTetromino::Update(WorldState& curWorldState)
	{
		//After a set amount of time, trigger a gravity event.
		//We reuse the key down event to get the effect of gravity
		mElapsedTime += (float)curWorldState.GetGameTime().ElapsedGameTime();
		if (mElapsedTime > mGravityInterval)
		{
			mElapsedTime = 0;

			if (mPlayer == 1)
			{
				//Create a message, set its subtype, world, and give it an auxillary "Key" attribute containing the key that was pressed (as a string);
				EventMessageAttributed message;
				message.SetWorld(curWorldState.GetWorld());
				message.SetSubtype("Keyboard");
				Datum& datum = message.Append("Key");
				datum.SetType(Datum::DatumType::STRING);
				datum.Set("S");

				Datum& datum2 = message.Append("Player");
				datum2.SetType(Datum::DatumType::INTEGER);
				datum2.Set(1);

				//Make an event out of the message and enqueue it in the world's queue
				std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
				for (auto& it : mBlocks)
				{
					it->Notify(event.get());
				}

			}
			else if (mPlayer == 2)
			{
				//Create a message, set its subtype, world, and give it an auxillary "Key" attribute containing the key that was pressed (as a string);
				EventMessageAttributed message;
				message.SetWorld(curWorldState.GetWorld());
				message.SetSubtype("Keyboard");
				Datum& datum = message.Append("Key");
				datum.SetType(Datum::DatumType::STRING);
				datum.Set("Down");

				Datum& datum2 = message.Append("Player");
				datum2.SetType(Datum::DatumType::INTEGER);
				datum2.Set(2);

				//Make an event out of the message and enqueue it in the world's queue
				std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
				for (auto& it : mBlocks)
				{
					it->Notify(event.get());
				}
			}

		}

		//Updates all the entities in the sector
		Sector::Update(curWorldState);

		//Check whether to lock or unlock rotation for this tetromino (based on a time constant
		if (mPlayer != 0)
		{

			if (mRotateCooldown)
			{
				if (mSFClock.getElapsedTime().asSeconds() > mRotateCooldownAmount)
				{
					mRotateCooldown = false;
					mSFClock.restart();
				}
			}
			
			if (mUndoRotate)
			{
				for (auto& it : mBlocks)
				{
					it->RevertState();
				}
				mPlayRotate = false;
			}
			
			if (mPlayRotate)
			{
				mRotateCooldown = true;
				if (GetWorld() != nullptr)
				{
					Library::CreateAudioEvent("Rotate", GetWorld()->As<World>());
				}
				mPlayRotate = false;

			}
			mUndoRotate = false;

			//Check collisions for all blocks and move them appropriately
			for (auto& it : mBlocks)
			{
				vector<std::string> collision = it->CheckCollisions();
				for (auto& str : collision)
				{
					if (str == "Right")
					{
						for (auto& block : mBlocks)
						{
							block->SetPosition(block->GetX() + 32, block->GetY());

						}

					}
					if (str == "Left")
					{
						for (auto& block : mBlocks)
						{
							block->SetPosition(block->GetX() - 32, block->GetY());
						}

					}

					if (str == "Top")
					{
						for (auto& block : mBlocks)
						{
							block->SetPosition(block->GetX(), block->GetY() - 32);
							// The SectorTetromino is locked into place (without delay, for now)
							// because at least one of its Block Entities collided with something
							// below it...
							mBlockLock = true;
							int player = Find("Player")->Get<int>();
							if (player == 1)
							{
								block->Find("BlockColor")->Set((std::string)"Blue");
							}
							else
							{
								block->Find("BlockColor")->Set((std::string)"Pink");
							}
							
						}

						mBlockLock = true;
					}

					if (str == "Bottom")
					{
						for (auto& block : mBlocks)
						{
							block->SetPosition(block->GetX(), block->GetY() + 32);
						}
					}
				}
			}
		}

		//See if one of our blocks indicated that our tetromino needs to be locked
		if (mBlockLock)
		{
			mBlockLock = false;
			Lock();
		}

		//Render all blocks in this tetromino
		for (auto& it : mBlocks)
		{
			it->Render(curWorldState);
		}
	}

	/**
	*Indicates that a block is locked in place and cannot be controlled by movement any longer
	*/
	void SectorTetromino::Lock()
	{
		if (!mLock)
		{
			//Play a lock sound
			Library::CreateAudioEvent("Touch", GetWorld()->As<World>());
		}
		//Set out lock flag
		mLock = true;

	}

	/**
	*Returns whether the sector is locked or not
	*
	*@return whether the sector is locked or not
	*/
	bool SectorTetromino::IsLocked() const
	{
		return mLock;
	}

	/**
	*Add a block to our block list
	*
	*@param block = the block to add
	*/
	void SectorTetromino::AddBlock(BlockEntity* block)
	{
		//If the block is valid
		if (block != nullptr)
		{
			//Make sure the block is not in the list
			uint32_t i = 0;
			for (i = 0; i < mBlocks.size(); ++i)
			{
				if (mBlocks[i] == block)
				{
					break;
				}
			}

			if (i == mBlocks.size())
			{
				//Add the block to the block list, set its position, and sets its player number
				mBlocks.push_back(block);
				int index = mBlocks.size() - 1;
				float x = mX + 32.0f * (int)(index % 4);
				float y = mY + 32.0f * (int)(index / 4);
				mBlocks.back()->SetPosition(x, y);
				mBlocks.back()->SetPlayer(mPlayer);
			}
		}
	}

	/**
	*Remove a block to our block list
	*
	*@param block = the block to remove
	*/
	void SectorTetromino::RemoveBlock(BlockEntity* block)
	{
		//Make sure the block is not null and is in the list
		if (block != nullptr)
		{
			uint32_t i = 0;
			for (i = 0; i < mBlocks.size(); ++i)
			{
				if (mBlocks[i] == block)
				{
					break;
				}
			}

			if (i < mBlocks.size())
			{
				mBlocks.erase(mBlocks.begin() + i);
			}
		}
	}


	/**
	*Sets the player the player (1 or 2) that owns this sector
	*
	*@param newPlayer = the player (1 or 2) that owns this sector
	*/
	void SectorTetromino::SetPlayer(const int& newPlayer)
	{
		mPlayer = newPlayer;

		for (auto& block : mBlocks)
		{
			block->SetPlayer(newPlayer);
		}
	}

	/**
	*Return a vector reference to the list of blocks in this sectors
	*
	*@return a vector reference to the list of blocks in this sectors
	*/
	std::vector<BlockEntity*>& SectorTetromino::GetBlocks()
	{
		return mBlocks;
	}

	/**
	*Returns the current x position of this sector
	*
	*@return the current x position of this sector
	*/
	float SectorTetromino::GetX() const
	{
		return mX;
	}

	/**
	*Returns the current y position of this sector
	*
	*@return the current y position of this sector
	*/
	float SectorTetromino::GetY() const
	{
		return mY;
	}

	/**
	*Sets the x position of this sector
	*Also sets the x-positions of the individual blocks in the sector.
	*/
	void SectorTetromino::SetX(float x)
	{
		mX = x;
		for (std::uint32_t i = 0; i < mBlocks.size(); i++)
		{
			float x = mX + 32.0f * (int)(i % 4);
			float y = mY + 32.0f * (int)(i / 4);
			mBlocks[i]->SetPosition(x, y);
		}
	}

	/**
	*Sets the y position of this sector
	*Also sets the y-positions of the individual blocks in the sector.
	*/
	void SectorTetromino::SetY(float y)
	{
		mY = y;
		for (std::uint32_t i = 0; i < mBlocks.size(); i++)
		{
			float x = mX + 32.0f * (int)(i % 4);
			float y = mY + 32.0f * (int)(i / 4);
			mBlocks[i]->SetPosition(x, y);
		}
	}


}


