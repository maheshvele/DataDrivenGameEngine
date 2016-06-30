#include "pch.h"
#include "BlockEntity.h"
#include "SectorTetromino.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include "World.h"
#include "Vector.h"
using namespace std;
namespace Library
{
	//Static member declaration
	std::vector<BlockEntity*> BlockEntity::blocks;

	RTTI_DEFINITIONS(BlockEntity);

	/**
	*Class constructor that initializes all data members
	*
	*/
	BlockEntity::BlockEntity() : Entity(""), mPlayer(), mX(0), mY(0), mW(32), mH(32), mRenderer(*TetrominoRender::GetInstance()), mOldX(0), mOldY(0), mCollider(mX, mY, mW, mH), lastDirection(), mState(0), mWasNotified(false)
	{
		InternalAttribute(State, 1, Datum::INTEGER, &mState);
		InternalAttribute(value, 4, Datum::DatumType::INTEGER, mValues);
		InternalAttribute(Player, 1, Datum::DatumType::INTEGER, &mPlayer);

		int num = 0;
		InternalAttribute(LeftXBound, 1, Datum::DatumType::INTEGER, &num);
		int num2 = 1024;
		InternalAttribute(RightXBound, 1, Datum::DatumType::INTEGER, &num2);
		int num3 = bottomBounds;
		InternalAttribute(BottomBound, 1, Datum::DatumType::INTEGER, &num3);


		Event<EventMessageAttributed>::Subscribe(this);
		blocks.push_back(this);
		Populate();
	}


	/**
	*Class constructor that initializes all data members
	*
	*@param name = the name of this entity
	*@param playerNumber = the owner of this block (int, 1 or 2)
	*/
	BlockEntity::BlockEntity(std::string name, std::uint32_t player) : Entity(name), mPlayer(player), mX(0), mY(0), mW(32), mH(32), mRenderer(*TetrominoRender::GetInstance()), mOldX(0), mOldY(0), mCollider(mX, mY, mW, mH), lastDirection(), mState(0), mWasNotified(false)
	{
		InternalAttribute(State, 1, Datum::INTEGER, &mState);
		InternalAttribute(value, 4, Datum::DatumType::INTEGER, mValues);
		InternalAttribute(Player, 1, Datum::DatumType::INTEGER, &mPlayer);

		if (mPlayer == 1)
		{
			int num = p1LeftBound;
			InternalAttribute(LeftXBound, 1, Datum::DatumType::INTEGER, &num);
			int num2 = p1RightBound;
			InternalAttribute(RightXBound, 1, Datum::DatumType::INTEGER, &num2);
			int num3 = bottomBounds;
			InternalAttribute(BottomBound, 1, Datum::DatumType::INTEGER, &num3);
		}
		else
		{
			int num = p2LeftBound;
			InternalAttribute(LeftXBound, 1, Datum::DatumType::INTEGER, &num);

			int num2 = p2RightBound;
			InternalAttribute(RightXBound, 1, Datum::DatumType::INTEGER, &num2);
			int num3 = bottomBounds;
			InternalAttribute(BottomBound, 1, Datum::DatumType::INTEGER, &num3);
		}
		Event<EventMessageAttributed>::Subscribe(this);
		blocks.push_back(this);
		Populate();
		auto& colorDatum = (*this)["BlockColor"];
		colorDatum.SetType(Datum::DatumType::STRING);
		colorDatum = std::string("Green");
	}

	/**
	*Copy constructor that does a deep copy of all members
	*
	*@param rhs = the block to become
	*/
	BlockEntity::BlockEntity(const BlockEntity& rhs) : Entity(""), mPlayer(rhs.mPlayer), mX(0), mY(0), mW(32), mH(32), mRenderer(*TetrominoRender::GetInstance()), mOldX(0), mOldY(0), mCollider(mX, mY, mW, mH), lastDirection(), mState(rhs.mState), mWasNotified(false)
	{
		InternalAttribute(State, 1, Datum::INTEGER, &mState);
		InternalAttribute(value, 4, Datum::DatumType::INTEGER, mValues);
		InternalAttribute(Player, 1, Datum::DatumType::INTEGER, &mPlayer);
		Populate();

		Event<EventMessageAttributed>::Subscribe(this);
		blocks.push_back(this);
		//Get the states
		auto values = rhs.Find("value");
		SetStates(values->Get<int>(0), values->Get<int>(1), values->Get<int>(2), values->Get<int>(3));

		auto* rhsColorDatum = rhs.Find("BlockColor");
		auto& colorDatum = (*this)["BlockColor"];
		colorDatum.SetType(Datum::DatumType::STRING);
		colorDatum = rhsColorDatum->Get<std::string>();

	}

	/**
	*@Destructor that deallocates all memory allocated by this class
	*/
	BlockEntity::~BlockEntity()
	{
		if (GetSector() != nullptr && GetSector()->As<SectorTetromino>())
		{
			GetSector()->As<SectorTetromino>()->RemoveBlock(this);
		}
		uint32_t i = 0;
		for (i = 0; i < blocks.size(); ++i)
		{
			if (blocks[i] == this)
			{
				break;
			}
		}

		if (i < blocks.size())
		{
			blocks.erase(blocks.begin() + i);
		}
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	/**
	*Unlocks key input, allowing us to once again move next frame.
	*
	*@param state = The current world state
	*/
	void BlockEntity::Update(WorldState& curWorldState)
	{
		mWasNotified = false;
	}

	/**
	*Called when an event is fired, we veryify its subtype and react to it.
	*
	*@param publisher = the event we're being notified
	*/
	void BlockEntity::Notify(EventPublisher* publisher)
	{

		Scope* sector = GetSector();
		if (sector == nullptr)
		{
			return;
		}
		SectorTetromino* sectorTetromino= sector->As<SectorTetromino>();
		if (sectorTetromino != nullptr && sectorTetromino->IsLocked() == false)
		{

			//If we haven't been notified yet this frame of a keyboard event (we only process one keyboard event per frame)
			if (!mWasNotified)
			{
				//See if we can handle the message
				Event<EventMessageAttributed>* message = publisher->As<Event<EventMessageAttributed>>();
				if (message != nullptr)
				{
					//If it's a keyboard pressed event
					if (message->Message().GetSubtype() == "Keyboard")
					{
						//If it's our player's input
						if (message->Message().Find("Player")->Get<int>() == (int)mPlayer)
						{
							//Get which ikey has been pressed and react
							std::string keyPressed = message->Message().Find("Key")->Get<std::string>();

							//If our player is player 1, react to the appropriate keys
							if (mPlayer == 1)
							{
								//Move up for W
								if (keyPressed == "Space")
								{
									SetPosition(mX, mY - 32);
									lastDirection = "Up";
									mWasNotified = true;

								}
								//Move left for A
								else if (keyPressed == "A")
								{
									SetPosition(mX - 32, mY);
									lastDirection = "Left";
									mWasNotified = true;

								}
								//Move right for D
								else if (keyPressed == "D")
								{
									SetPosition(mX + 32, mY);
									lastDirection = "Right";
									mWasNotified = true;
								}
								//Move down for S
								else if (keyPressed == "S")
								{
									SetPosition(mX, mY + 32);
									lastDirection = "Down";
									mWasNotified = true;
								}
							}

							//If our player is player 1, react to the appropriate keys
							else if (mPlayer == 2)
							{

								//Move up for Up Arrow
								if (keyPressed == "R")
								{
									SetPosition(mX, mY - 32);
									lastDirection = "Up";
									mWasNotified = true;
								}
								//Move left for Left Arrow
								else if (keyPressed == "Left")
								{
									SetPosition(mX - 32, mY);
									lastDirection = "Left";
									mWasNotified = true;
								}
								//Move right for Right Arrow
								else if (keyPressed == "Right")
								{
									SetPosition(mX + 32, mY);
									lastDirection = "Right";
									mWasNotified = true;

								}
								//Move down for Down Arrow
								else if (keyPressed == "Down")
								{
									SetPosition(mX, mY + 32);
									lastDirection = "Down";
									mWasNotified = true;
								}
							}
						}
					}

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
								//Rotate for R
								if (keyPressed == "W")
								{
									AdvanceState();
									mWasNotified = true;
								}
							}
							else if (mPlayer == 2)
							{
								//Rotate for R
								if (keyPressed == "Up")
								{
									AdvanceState();
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
	*Draws this block to the screen
	*
	*@param state = The current world state, which we pass to the underlying rendering function
	*/
	void BlockEntity::Render(WorldState& curWorldState)
	{
		auto values = Find("value");
		if (values->Get<int>(mState))
		{
			std::string color = Find("BlockColor")->Get<std::string>();
			if (color == "Blue")
			{
				mRenderer.RenderOnScreen(*(curWorldState.GetWorld()->GetWindow()), TetrominoRender::TextureType::BlueBlock, sf::Vector2f(mX, mY));
			}
			else if (color == "Green")
			{
				mRenderer.RenderOnScreen(*(curWorldState.GetWorld()->GetWindow()), TetrominoRender::TextureType::GreenBlock, sf::Vector2f(mX, mY));
			}
			else if (color == "Pink")
			{
				mRenderer.RenderOnScreen(*(curWorldState.GetWorld()->GetWindow()), TetrominoRender::TextureType::PinkBlock, sf::Vector2f(mX, mY));
			}
			else if (color == "Purple")
			{
				mRenderer.RenderOnScreen(*(curWorldState.GetWorld()->GetWindow()), TetrominoRender::TextureType::PurpleBlock, sf::Vector2f(mX, mY));
			}
			else if (color == "Yellow")
			{
				mRenderer.RenderOnScreen(*(curWorldState.GetWorld()->GetWindow()), TetrominoRender::TextureType::YellowBlock, sf::Vector2f(mX, mY));
			}
			else if (color == "Orange")
			{
				mRenderer.RenderOnScreen(*(curWorldState.GetWorld()->GetWindow()), TetrominoRender::TextureType::OrangeBlock, sf::Vector2f(mX, mY));
			}
		}
	}

	/**
	*Checks for collisions against other blocks and against the border
	*
	*@return a vector containing information about which side we collided on
	*/
	vector<std::string> BlockEntity::CheckCollisions()
	{
		vector<std::string> collisionInfo;

		//If this block is not "Active" (i.e. not being shown on the screen) it should not be considered for collisions
		if (Find("value")->Get<int>(mState) == 0)
		{
			return collisionInfo;
		}

		BlockToBlockCollisions(collisionInfo);
		BorderCollisions(collisionInfo);

		return collisionInfo;
	}

	/**
	*Checks the collision box of this block against all other blocks in the world
	*
	*@param collisionInfo = a list we push collision info to
	*/
	void BlockEntity::BlockToBlockCollisions(vector<std::string>& collisionInfo)
	{

		//Check collisions with other boxes
		for (auto& it : blocks)
		{
			if (it == this)
			{
				continue;
			}

			if (it->Find("value")->Get<int>(it->GetState()) == 0)
			{
				continue;
			}


			if (BoxCollider::CheckCollisions(mCollider, it->GetCollider()))
			{
				if (lastDirection == "Up")
				{
					if (mCollider.WasCollisionBottom(it->GetCollider()))
					{
						collisionInfo.push_back("Bottom");
					}
				}

				if (lastDirection == "Down")
				{
					if (mCollider.WasCollisionTop(it->GetCollider()))
					{
						collisionInfo.push_back("Top");
					}
				}

				if (lastDirection == "Right")
				{
					if (mCollider.WasCollisionLeft(it->GetCollider()))
					{
						collisionInfo.push_back("Left");
					}
				}

				if (lastDirection == "Left")
				{
					if (mCollider.WasCollisionRight(it->GetCollider()))
					{
						collisionInfo.push_back("Right");
					}
				}

				if (lastDirection == "Rotate")
				{
					collisionInfo.push_back("Top");
					collisionInfo.push_back("Bottom");
					collisionInfo.push_back("Right");
					collisionInfo.push_back("Left");
				}
			}

		}
	}


	/**
	*Checks the collision box of this borders of their tetris box
	*
	*@param collisionInfo = a list we push collision info to
	*/
	void BlockEntity::BorderCollisions(vector<std::string>& collisionInfo)
	{
		//Check left side collisions
		if (Find("LeftXBound")->Get<int>() > mX)
		{
			collisionInfo.push_back("Right");
		}

		//Check right side collisions
		if (Find("RightXBound")->Get<int>() < mX + mW)
		{
			collisionInfo.push_back("Left");
		}

		//Check bottom collisions
		if (Find("BottomBound")->Get<int>() < mY + mH)
		{
			collisionInfo.push_back("Top");
		}
	}

	/**
	*Gets the collider attached to this block
	*
	*@return a reference to the box collider attached to this block
	*/
	BoxCollider& BlockEntity::GetCollider()
	{
		return mCollider;
	}

	/**
	*Returns the current x position of this entity
	*
	*@return the current x position of this entity
	*/
	float BlockEntity::GetX()
	{
		return mX;
	}

	/**
	*Returns the current y position of this entity
	*
	*@return the current y position of this entity
	*/
	float BlockEntity::GetY()
	{
		return mY;
	}

	/**
	*Sets the current player number (1 or 2)
	*
	*@param player = which player controls this block (1 or 2)
	*/
	void BlockEntity::SetPlayer(uint32_t player)
	{
		mPlayer = player;
		if (mPlayer == 1)
		{
			(*this)["LeftXBound"] = 96;
			(*this)["RightXBound"] = 416;
			(*this)["BottomBound"] = 736;
		}
		else if (mPlayer == 2)
		{
			(*this)["LeftXBound"] = 608;
			(*this)["RightXBound"] = 928;
			(*this)["BottomBound"] = 736;
		}

		Find("Player")->Set((int)player);
	}


	/**
	*Sets the sector that contains us
	*
	*@param newSector = the sector to set as our containing sector
	*/
	void BlockEntity::SetSector(Scope* newSector)
	{
		Entity::SetSector(newSector);
		if (newSector->Is("SectorTetromino"))
		{
			newSector->As<SectorTetromino>()->AddBlock(this);
		}
	}

	/**
	*Sets the position of the block
	*
	*@param x = the x position to set our location
	*@param y = the y position to set our location
	*/
	void BlockEntity::SetPosition(float x, float y)
	{
		mX = x;
		mY = y;
		mCollider.SetX(mX);
		mCollider.SetY(mY);
	}

	/**
	*Gets the current rotation state of the block
	*
	*@return an integer corresponding to our rotation state
	*/
	int BlockEntity::GetState()
	{
		return mState;
	}

	/**
	*Sets a singular rotation state
	*
	*@param state = on or off state (0 or 1)
	*@param index = which state to set on or off
	*/
	void BlockEntity::SetState(uint32_t state, uint32_t index)
	{
		auto values = Find("value");
		values->Set((int)state, index);
	}

	/**
	*Sets on/off values for all 4 rotation states
	*
	*@param state0 = The first rotation state
	*@param state1 = The second rotation state
	*@param state2 = The third rotation state
	*@param state3 = The fourth rotation state
	*/
	void BlockEntity::SetStates(uint32_t state0, uint32_t state1, uint32_t state2, uint32_t state3)
	{
		auto values = Find("value");

		values->Set((int)state0, 0);
		values->Set((int)state1, 1);
		values->Set((int)state2, 2);
		values->Set((int)state3, 3);
	}

	/**
	*Advances our block to the next rotation state
	*/
	void BlockEntity::AdvanceState()
	{
		mState = (mState + 1) % STATES;
		lastDirection = "Rotate";
		if (!CheckCollisions().empty())
		{
			GetSector()->As<SectorTetromino>()->mUndoRotate = true;
		}
		else
		{
			GetSector()->As<SectorTetromino>()->mPlayRotate = true;
		}
	}

	/**
	*If we fail a rotation (i.e. the rotation collides with another block) call this function to undo the rotation.
	*/
	void BlockEntity::RevertState()
	{
		if (mState == 0)
		{
			mState = 3;
		}
		else
		{
			mState -= 1;
		}

	}

	/**
	*Returns the static list of all blocks currently in the game
	*
	*@a vector containing all of the blocks
	*/
	std::vector<BlockEntity*> BlockEntity::GetBlocks()
	{
		return blocks;
	}

	/**
	*Returns the player that owns this block
	*
	*@return an integer corresponding to the player number
	*/
	std::uint32_t BlockEntity::GetPlayer()
	{
		return mPlayer;
	}
}
