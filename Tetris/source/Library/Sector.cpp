#include "pch.h"
#include "Sector.h"

namespace Library
{
	RTTI_DEFINITIONS(Sector)

	//Default constructor
	Sector::Sector() :
		mName("")
	{
		ExternalAttribute(Name, Datum::STRING, 1, &mName)//Attribute that contains the name
		InternalAttribute(Entities, 1, Datum::TABLE, nullptr)//Attribute that contains the child scope of sectors
		Populate();
	}

	//Constructor
	Sector::Sector(const std::string& initialName) :
		mName(initialName)
	{
		ExternalAttribute(Name, Datum::STRING, 1, &mName)//Attribute that contains the name
		InternalAttribute(Entities, 1, Datum::TABLE, nullptr)//Attribute that contains the child scope of sectors
		Populate();
	}
	
	//Destructor
	Sector::~Sector()
	{
	}

	//Get the list of entities
	Scope* Sector::Entities() const
	{
		return Find("Entities")->Get<Scope*>();
	}

	//Get our name
	const std::string& Sector::Name() const
	{
		return mName;
	}

	//Adopt ourselves to a world
	void Sector::SetWorld(Scope* newWorld)
	{
		if (newWorld->Is("World"))
		{
			newWorld->Find("Sectors")->Get<Scope*>()->Adopt(this, mName, 0);
		}
	}

	//Get the world that we're in
	Scope* Sector::GetWorld() const
	{ 
		if (GetParent() == nullptr)
		{
			return nullptr;
		}
		return GetParent()->GetParent();
	}

	//Create a new entity using the entity factory
	Scope* Sector::CreateEntity(const std::string& className, const std::string& instanceName) const
	{
		Entity* newEntity = Factory<Scope>::Create(className)->As<Entity>();
		newEntity->Find("Name")->Get<std::string>() = instanceName;
		newEntity->SetSector(this->As<Scope>());
		return newEntity;
	}

	//Update all of the entities in this sector
	void Sector::Update(WorldState& curState)
	{
		Scope& curEntities = *Entities();

		for (std::uint32_t i = 0; i < curEntities.Size(); i++)
		{
			Scope* scope = curEntities[i].Get<Scope*>();
			if (scope != nullptr)
			{
				Entity* entity = scope->As<Entity>();
				if (entity != nullptr)
				{
					curState.SetEntity(entity);
					entity->Update(curState);
				}
			}
		}
	}

}