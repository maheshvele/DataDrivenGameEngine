#include "pch.h"
#include "Entity.h"

namespace Library
{
	RTTI_DEFINITIONS(Entity)

	//Constructor
	Entity::Entity() :
		mName("")
	{
		ExternalAttribute(Name, Datum::STRING, 1, &mName)
		InternalAttribute(Actions, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Constructor with a name
	Entity::Entity(const std::string& initialName) :
		mName(initialName)
	{
		ExternalAttribute(Name, Datum::STRING, 1, &mName)
		InternalAttribute(Actions, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Destructor
	Entity::~Entity()
	{
	}

	/*
	This was a first pass at copying entities. Leaving it in here for the case that
	we may return to it one day where a use case presents itself for copying entities, making it
	necessary to revisit this code.

	//Copy constructor
	Entity::Entity(const Entity& rhs) :
		mName(rhs.mName), Attributed(rhs)
	{
		Find("Name")->SetStorage(&mName, 1);
	}

	//Assignment operator
	Entity& Entity::operator=(const Entity& rhs)
	{
		mName = rhs.mName;
		Attributed::operator=(rhs);
		Find("Name")->SetStorage(&mName, 1);
		return *this;
	}
	*/

	//Get the name of the class
	const std::string& Entity::Name() const
	{
		return mName;
	}	

	//Get the address of the current sector we're in (the parent)
	Scope* Entity::GetSector() const
	{
		if (GetParent() == nullptr)
		{
			return nullptr;
		}
		return GetParent()->GetParent();
	}

	//Adopt us into a sector
	void Entity::SetSector(Scope* newSector)
	{
		if (newSector->Is("Sector"))
		{
			newSector->Find("Entities")->Get<Scope*>()->Adopt(this, mName, 0);
		}
	}
	
	//Get the list of entities
	Scope* Entity::Actions() const
	{
		return Find("Actions")->Get<Scope*>();
	}

	//Create a new action via the factory
	Scope* Entity::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Scope* newAction = Factory<Action>::Create(className)->As<Action>();
		newAction->Find("Name")->Get<std::string>() = instanceName;
		newAction->As<Action>()->SetEntity(this->As<Scope>());
		return newAction;
	}

	//Update all of our actions
	void Entity::Update(WorldState& curWorldState)
	{
		Scope& curActions = *Actions();
		for (std::uint32_t i = 0; i < curActions.Size(); i++)
		{
			Scope* scope = curActions[i].Get<Scope*>();
			if (scope != nullptr)
			{
				Action* action = scope->As<Action>();
				if (action != nullptr)
				{
					action->Update(curWorldState);
				}
			}
		}
	}

}