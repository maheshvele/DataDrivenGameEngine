#include "pch.h"
#include "Action.h"

namespace Library
{
	RTTI_DEFINITIONS(Action)

	//Default constructor
	Action::Action() :
		mName("")
	{
		ExternalAttribute(Name, Datum::STRING, 1, &mName)
		Populate();
	}

	//Constructor with a name
	Action::Action(const std::string& initialName) :
		mName(initialName)
	{
		ExternalAttribute(Name, Datum::STRING, 1, &mName)
		Populate();
	}

	//Destructor
	Action::~Action()
	{
	}

	//Getter for current name
	std::string& Action::Name()
	{
		return mName;
	}

	//Get the address of our containing entity
	Scope* Action::GetContainer()
	{
		return GetParent()->GetParent();
	}

	//Adopt us into an entity's action scope
	void Action::SetEntity(Scope* newEntity)
	{
		if (newEntity->Is("Entity"))
		{
			newEntity->Find("Actions")->Get<Scope*>()->Adopt(this, mName, 0);
		}
	}

}