#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Sector.h"
#include "pch.h"
#include "SFML\System.hpp"


namespace Library
{
	class BlockEntity;
	class SectorTetromino final : public Sector
	{
		RTTI_DECLARATIONS(SectorTetromino, Sector);

	public:
		/*
		/brief static characters to use for comparison with the board.
		*/
		static const char EMPTY = '_', OCCUPIED = 'O', PIVOT = 'P';

		/*
		/brief Inherited constructor and destructors from Entity.
		*/
		explicit SectorTetromino(const std::string& name = "", uint32_t player = 0);
		
		virtual ~SectorTetromino() = default;

		/**
		Copy constructor
		*/
		SectorTetromino(const SectorTetromino& rhs);

		/*
		/brief Sets the configuration to the next one.
		*/
		void ShiftConfiguration();

		/**
		*Takes a WorldState reference and updates all of the actions in our action list
		*
		*@param curWorldState the current state of the world
		*/
		void Update(WorldState& curWorldState) override;

		/**
		*Locks the 
		*/
		void Lock();

		/**
		*Returns whether the sector is locked or not
		*
		*@return whether the sector is locked or not
		*/
		bool IsLocked() const;

		/**
		*Add a block to our block list
		*
		*@param block = the block to add
		*/
		void AddBlock(BlockEntity* block);

		/**
		*Remove a block to our block list
		*
		*@param block = the block to remove
		*/
		void RemoveBlock(BlockEntity* block);

		/**
		*Sets the player the player (1 or 2) that owns this sector
		*
		*@param newPlayer = the player (1 or 2) that owns this sector
		*/
		void SetPlayer(const int& newPlayer);

		/**
		*Return a vector reference to the list of blocks in this sectors
		*
		*@return a vector reference to the list of blocks in this sectors
		*/
		std::vector<BlockEntity*>& GetBlocks();

		/**
		*Returns the current x position of this sector
		*
		*@return the current x position of this sector
		*/
		float GetX() const;

		/**
		*Returns the current y position of this sector
		*
		*@return the current y position of this sector
		*/
		float GetY() const;

		/**
		*Sets the x position of this sector
		*/
		void SetX(float x);

		/**
		*Sets the y position of this sector
		*/
		void SetY(float y);

	public:
		bool mUndoRotate;
		bool mPlayRotate;
		bool mRotateCooldown;
		bool mBlockLock;
		const float HORIZ_SPEED = 1;
		static const uint32_t DIMENSIONS = 4, STATES = 4;


	private:
		bool mLock;
		int32_t mWidth, mHeight, mPlayer;
		float mRotateCooldownAmount;
		std::vector<BlockEntity*> mBlocks;
		float mX, mY;
		sf::Clock mSFClock;
		float mElapsedTime;
		float mGravityInterval;

		/**
		Will hold all the possible block colors that we can randomly assign when spawning the blocks
		*/
		static const std::string PossibleColors[];
		static const std::uint32_t NumberOfPossibleColors;
	};
}

