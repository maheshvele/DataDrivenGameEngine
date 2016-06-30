#include "pch.h"
#include "SharedDataWorld.h"

namespace Library
{

	RTTI_DEFINITIONS(SharedDataWorld);

	//Default constructor
	SharedDataWorld::SharedDataWorld() :
		mWorld(nullptr), mCurSector(nullptr), mCurEntity(nullptr), mIsClone(false)
	{
	}

	//Constructor with a defined initial scope
	SharedDataWorld::SharedDataWorld(World* initialWorld) :
		mWorld(initialWorld), mCurSector(nullptr), mCurEntity(nullptr), mIsClone(false)
	{
	}

	//Destructor
	SharedDataWorld::~SharedDataWorld()
	{
	}

	//Getter for the world we're filling out
	World* SharedDataWorld::GetWorld()
	{
		return mWorld;
	}

	//Setter for the world we're filling out
	void SharedDataWorld::SetWorld(World* newWorld)
	{
		mWorld = newWorld;
	}

	//Getter for the current sector
	Sector* SharedDataWorld::GetSector()
	{
		return mCurSector;
	}

	//Setter for the current sector
	void SharedDataWorld::SetSector(Scope* newSector)
	{
		//Check if we're just trying to clear the field
		if (newSector == nullptr)
		{
			mCurSector = nullptr;
			return;
		}


		mCurSector = newSector->As<Sector>();
		if (!mCurSector)
		{
			throw std::exception("Non-sector scope argument used to set sector");
		}
	}


	//Getter for the current entity
	Entity* SharedDataWorld::GetEntity()
	{
		return mCurEntity;
	}

	//Setter for the current Entity
	void SharedDataWorld::SetEntity(Scope* newEntity)
	{
		//Check if we're just trying to clear the field
		if (newEntity == nullptr)
		{
			mCurEntity = nullptr;
			return;
		}

		mCurEntity = newEntity->As<Entity>();
		if (!mCurEntity)
		{
			throw std::exception("Non-Entity scope argument used to set entity");
		}
	}

	//Getter for current action
	Action* SharedDataWorld::GetAction()
	{
		return mCurAction;
	}

	//Setter for current action
	void SharedDataWorld::SetAction(Action* newAction)
	{
		//Check if we're just trying to clear the field
		if (newAction == nullptr)
		{
			mCurAction = nullptr;
			return;
		}

		mCurAction = newAction->As<Action>();
		if (!mCurAction)
		{
			throw std::exception("Non-Action scope argument used to set action");
		}
	}

	//Clone
	SharedDataWorld* SharedDataWorld::Clone()
	{
		SharedDataWorld* returnVal = new SharedDataWorld();
		returnVal->mIsClone = true;
		return returnVal;
	}
}