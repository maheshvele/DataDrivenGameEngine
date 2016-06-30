#include "pch.h"
#include "ActionCreateEntity.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionCreateEntity)

	//Default constructor
	ActionCreateEntity::ActionCreateEntity() :
		Action(""), mInstanceName(""), mClassName("Entity")
	{
	}

	//Named constructor
	ActionCreateEntity::ActionCreateEntity(const std::string& name) :
		Action(name), mInstanceName(""), mClassName("Entity")
	{
	}

	//Destructor
	ActionCreateEntity::~ActionCreateEntity()
	{
	}

	//Getter for class name
	std::string ActionCreateEntity::GetClass()
	{
		return mClassName;
	}

	//Setter for class name
	void ActionCreateEntity::SetClass(const std::string& name)
	{
		mClassName = name;
	}

	//Getter for instance name
	std::string ActionCreateEntity::GetInstanceName()
	{
		return mInstanceName;
	}

	//Setter for instance name
	void ActionCreateEntity::SetInstanceName(const std::string& name)
	{
		mInstanceName = name;
	}

	//Create a new entity in our containing sector
	void ActionCreateEntity::Update(const WorldState& curState)
	{
		Scope* container = GetContainer();

		while (!container->Is("Sector"))
		{
			container = container->GetParent();
		}

		Sector* sector = container->As<Sector>();



		if (sector != nullptr)
		{
			sector->CreateEntity(mClassName, mInstanceName);
		}
	}

}