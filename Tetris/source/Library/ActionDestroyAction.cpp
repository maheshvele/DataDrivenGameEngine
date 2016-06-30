#include "pch.h"
#include "ActionDestroyAction.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionDestroyAction)

	ActionDestroyAction::ActionDestroyAction() :
		Action("")//, mTarget("")
	{
		InternalAttribute(Target, 1, Datum::STRING, nullptr)
		Populate();
	}

	ActionDestroyAction::ActionDestroyAction(const std::string& newName) :
		Action(newName)//, mTarget("")
	{
		InternalAttribute(Target, 1, Datum::STRING, nullptr)
		Populate();
	}

	ActionDestroyAction::~ActionDestroyAction()
	{
	}

	void ActionDestroyAction::Update(const WorldState& curState)
	{
		Scope* curParent = GetParent();
		if (curParent != nullptr)
		{
			Datum* targetDatum = curParent->Find(GetTargetName());
			if (targetDatum != nullptr)
			{
				Scope* targetScope = targetDatum->Get<Scope*>();
				targetScope->Orphan();
				delete targetScope;
				targetDatum->Set((Scope*)nullptr);
			}
		}
	}

	std::string ActionDestroyAction::GetTargetName()
	{
		return Find("Target")->Get<std::string>();
	}

	void ActionDestroyAction::SetTargetName(const std::string& newName)
	{
		Find("Target")->Set(newName);//mTarget = newName;
	}

}