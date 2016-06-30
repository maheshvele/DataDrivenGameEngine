#include "pch.h"
#include "ActionAdopt.h"
#include "World.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionAdopt)

	//Default constructor
	ActionAdopt::ActionAdopt() :
		Action("")
	{
		InternalAttribute(Target, 1, Datum::STRING, nullptr)
		Populate();
	}

	//Name constructor
	ActionAdopt::ActionAdopt(const std::string& name) :
		Action(name)
	{
		InternalAttribute(Target, 1, Datum::STRING, nullptr)
		Populate();
	}

	//Destructor
	ActionAdopt::~ActionAdopt()
	{
	}

	/**
	The update function of ActionAdopt calls the setSector method of
	the entity that contains this action on the provided target sector.
	This should produce the behavior of orphaning the entity and moving it
	into a new sector

	@param curState the current worldstate to reference during update
	*/
	void ActionAdopt::Update(const WorldState& curState)
	{
		//Double check to ensure that our target sector isn't the one
		//that our containing entity already exists in
		std::string targetName = Find("Target")->Get<std::string>();
		Sector* curSector = curState.GetSector();
		if (targetName == curSector->Name())
		{
			return;
		}

		//Grab the entity that contains us
		Entity* curEntity = curState.GetEntity();
		
		//Grab the world
		World* curWorld = curState.GetWorld();

		//Set up the sector
		Datum* targetDatum = curWorld->Sectors()->Find(targetName);
		if (targetDatum == nullptr || targetDatum->GetType() != Datum::TABLE)
		{
			throw std::exception("Sector could not be found");
		}
		else		
		{
			Sector* targetSector = targetDatum->Get<Scope*>()->As<Sector>();
			if (targetSector == nullptr)
			{
				throw std::exception("Malformed sector");
			}
			else
			{
				curEntity->SetSector(targetSector);
				return;
			}
		}
	}

	//Getter for target sector
	std::string ActionAdopt::GetTargetSector() const
	{
		return Find("Target")->Get<std::string>();
	}

	//Setter for the sector that we're going to be adopted into
	void ActionAdopt::SetTargetSector(const std::string& string)
	{
		Find("Target")->Set(string);
	}

}