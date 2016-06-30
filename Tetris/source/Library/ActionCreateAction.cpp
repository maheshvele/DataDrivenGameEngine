#include "pch.h"
#include "ActionCreateAction.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionCreateAction)

	//Default constructor
	ActionCreateAction::ActionCreateAction() :
		Action("")//, mPrototype(""), mCreationName("")
	{
		InternalAttribute(PrototypeName, 1, Datum::STRING, nullptr)
		InternalAttribute(CreationName, 1, Datum::STRING, nullptr)
		Populate();
	}

	//Constructor with a name
	ActionCreateAction::ActionCreateAction(const std::string& initialName) :
		Action(initialName)//, mPrototype(""), mCreationName("")
	{
		InternalAttribute(PrototypeName, 1, Datum::STRING, nullptr)
		InternalAttribute(CreationName, 1, Datum::STRING, nullptr)
		Populate();
	}

	//Destructor
	ActionCreateAction::~ActionCreateAction()
	{
	}

	//Getter for prototype name
	std::string ActionCreateAction::GetPrototypeName()
	{
		return Find("PrototypeName")->Get<std::string>();//mPrototype;
	}

	//Setter for prototype name
	void ActionCreateAction::SetPrototypeName(const std::string& newName)
	{
		Find("PrototypeName")->Set(newName);//mPrototype = newName;
	}

	//Getter for instance name
	std::string ActionCreateAction::GetCreationName()
	{
		return Find("CreationName")->Get<std::string>();//mCreationName;
	}

	//Setter for instance name
	void ActionCreateAction::SetCreationName(const std::string& newName)
	{
		Find("CreationName")->Set(newName);//mCreationName = newName;
	}


	//Create a new action based on our prototype name and instance name
	void ActionCreateAction::Update(const WorldState& curState)
	{
		Action* newAction = Factory<Action>::Create(GetPrototypeName())->As<Action>();
		newAction->Find("Name")->Get<std::string>() = GetCreationName();
		GetParent()->Adopt(newAction, newAction->Name(), 0);
	}
}