#pragma once
#include <vector>
#include "Entity.h"
#include "EventSubscriber.h"
#include "TetrominoRender.h"

namespace Library
{
	
	class BlockEntity final: public Entity, public EventSubscriber
	{
		RTTI_DECLARATIONS(BlockEntity, Entity);
		friend class Board;
	public:
		static const uint32_t STATES = 4;

		/**
		*Class constructor that initializes all data members
		*
		*/
		BlockEntity();

		/**
		*Class constructor that initializes all data members
		*
		*@param name = the name of this entity
		*@param playerNumber = the owner of this block (int, 1 or 2)
		*/
		BlockEntity(std::string name, std::uint32_t playerNumber);

		/**
		*@Destructor that deallocates all memory allocated by this class
		*/
		~BlockEntity();

		/**
		*Copy constructor that does a deep copy of all members
		*
		*@param rhs = the block to become
		*/
		BlockEntity(const BlockEntity& rhs);

		/**
		*Unlocks key input, allowing us to once again move next frame.
		*
		*@param state = The current world state
		*/
		void Update(WorldState& state) override;

		/**
		*Called when an event is fired, we veryify its subtype and react to it.
		*
		*@param publisher = the event we're being notified
		*/
		void Notify(EventPublisher* publisher) override;

		/**
		*Draws this block to the screen
		*
		*@param state = The current world state, which we pass to the underlying rendering function
		*/
		void Render(WorldState& state);

		/**
		*Checks for collisions against other blocks and against the border
		*
		*@return a vector containing information about which side we collided on
		*/
		std::vector<std::string> CheckCollisions();

		/**
		*Checks the collision box of this block against all other blocks in the world
		*
		*@param collisionInfo = a list we push collision info to
		*/
		void BlockToBlockCollisions(std::vector<std::string>& collisionInfo);

		/**
		*Checks the collision box of this borders of their tetris box
		*
		*@param collisionInfo = a list we push collision info to
		*/
		void BlockEntity::BorderCollisions(std::vector<std::string>& collisionInfo);


		/**
		*Gets the collider attached to this block
		*
		*@return a reference to the box collider attached to this block
		*/
		BoxCollider& GetCollider();

		/**
		*Returns the current x position of this entity
		*
		*@return the current x position of this entity
		*/
		float GetX();

		/**
		*Returns the current y position of this entity
		*
		*@return the current y position of this entity
		*/
		float GetY();

		/**
		*Sets the current player number (1 or 2)
		*
		*@param player = which player controls this block (1 or 2)
		*/
		void SetPlayer(uint32_t player);

		/**
		*Sets the sector that contains us
		*
		*@param newSector = the sector to set as our containing sector
		*/
		void SetSector(Scope* newSector) override;

		/**
		*Sets the position of the block
		*
		*@param x = the x position to set our location
		*@param y = the y position to set our location
		*/
		void SetPosition(float x, float y);

		/**
		*Gets the current rotation state of the block
		*
		*@return an integer corresponding to our rotation state
		*/
		int GetState();

		/**
		*Sets a singular rotation state
		*
		*@param state = on or off state (0 or 1)
		*@param index = which state to set on or off
		*/
		void SetState(uint32_t state, uint32_t index);

		/**
		*Sets on/off values for all 4 rotation states
		*
		*@param state0 = The first rotation state
		*@param state1 = The second rotation state
		*@param state2 = The third rotation state
		*@param state3 = The fourth rotation state
		*/
		void SetStates(uint32_t state0, uint32_t state1, uint32_t state2, uint32_t state3);

		/**
		*Advances our block to the next rotation state
		*/
		void AdvanceState();

		/**
		*If we fail a rotation (i.e. the rotation collides with another block) call this function to undo the rotation.
		*/
		void RevertState();


		/**
		*Returns the static list of all blocks currently in the game
		*
		*@a vector containing all of the blocks
		*/
		static std::vector<BlockEntity*> GetBlocks();

		/**
		*Returns the player that owns this block
		*
		*@return an integer corresponding to the player number
		*/
		std::uint32_t GetPlayer();


		/**
		* Constant values used for bounding each block of the Tetromino.
		* Player 1 and 2 shared a common bottom boundary but their left and right bounds differ
		*/
		static const int p1LeftBound = 96;
		static const int p1RightBound = 416;
		static const int p2LeftBound = 608;
		static const int p2RightBound = 928;
		static const int bottomBounds = 736;

	private:
		bool mWasNotified;
		std::uint32_t mState;
		std::string lastDirection;
		std::uint32_t mValues[4];
		std::uint32_t mPlayer;
		float mX, mY, mW, mH;
		float mOldX, mOldY;
		TetrominoRender& mRenderer;
		static std::vector<BlockEntity*> blocks;
		BoxCollider mCollider;


	};
}
