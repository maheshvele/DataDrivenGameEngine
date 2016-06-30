#include "pch.h"
#include "ActionList.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	//Default constructor
	ActionList::ActionList() :
		Action("")
	{
		InternalAttribute(Actions, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Constructor with a name
	ActionList::ActionList(const std::string& initialName) :
		Action(initialName)
	{
		InternalAttribute(Actions, 1, Datum::TABLE, nullptr)
		Populate();
	}

	//Destructor
	ActionList::~ActionList()
	{
	}

	//Get the scope containing our actions
	Scope* ActionList::Actions()
	{
		return Find("Actions")->Get<Scope*>();
	}

	//Create a new subaction and adopt it into our list
	Scope* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Scope* newAction = Factory<Action>::Create(className)->As<Action>();
		std::string& actionName = newAction->Find("Name")->Get<std::string>();
		actionName = instanceName;
		Actions()->Adopt(newAction, actionName, 0);
		return newAction;
	}

	//Update all of the actions in our action list
	void ActionList::Update(const WorldState& curState)
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
					action->Update(curState);
				}
			}
		}
	}
}