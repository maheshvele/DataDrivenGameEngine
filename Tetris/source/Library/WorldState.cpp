#include "pch.h"
#include "WorldState.h"

namespace Library
{
	WorldState::WorldState() :
		mTime()
	{
	}

	WorldState::~WorldState()
	{
	}

	GameTime& WorldState::GetGameTime()
	{
		return mTime;
	}

	const GameTime& WorldState::GetGameTime() const
	{
		return mTime;
	}

	void WorldState::SetGameTime(const GameTime& newGameTime)
	{
		mTime = newGameTime;
	}

	World* WorldState::GetWorld() const
	{
		return mCurWorld;
	}

	void WorldState::SetWorld(World* newWorld)
	{
		mCurWorld = newWorld;
	}

	Sector* WorldState::GetSector() const
	{
		return mCurSector;
	}

	void WorldState::SetSector(Sector* newSector)
	{
		mCurSector = newSector;
	}

	Entity* WorldState::GetEntity() const
	{
		return mCurEntity;
	}

	void WorldState::SetEntity(Entity* newEntity)
	{
		mCurEntity = newEntity;
	}

}