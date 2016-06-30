#include "pch.h"
#include "ActionIf.h"
#include "Sector.h"
#include <sstream>

namespace Library
{
	RTTI_DEFINITIONS(ActionIf)

	ActionIf::ActionIf(const std::string& name)
	: ActionList(name), mConditionDatum(nullptr)
	{
		InternalAttribute(Condition, 1, Datum::INTEGER, nullptr)
		Populate();
	}

	/*
	The end user needs to place, in XML, Actions (or ActionLists) labeled as
	'Then' and 'Else', and then the Update loop for those Actions will occur
	or not occur based on the current state of the condition, mCondition.
	*/
	void ActionIf::Update(const WorldState& worldState)
	{
		if (mConditionDatum != nullptr)
		{
			// Need to make sure the Datum is of type <int>
			Find("Condition")->Set(mConditionDatum->Get<int>(0));
		}

		// If 'Condition' is not initialized, the default condition
		// evaluates to false, because it is a nullptr (i.e., 0)
		if (Find("Condition")->Get<int>())
		{
			if ((*this)["Actions"].Get<Scope*>()->Find("Then"))
			{
				(*this)["Actions"].Get<Scope*>()->Find("Then")->Get<Scope*>()->As<ActionList>()->Update(worldState);
			}
			else
			{
				throw new std::exception("Cannot find 'Then' statement/ActionList.");
			}
		}
		else
		{
			if ((*this)["Actions"].Get<Scope*>()->Find("Else") && !(*this)["Actions"].Get<Scope*>()->Find("Then"))
			{
				throw new std::exception("Cannot find accompanying 'Then' statement/ActionList to current 'Else' statement.");
			}
			else if ((*this)["Actions"].Get<Scope*>()->Find("Else"))
			{
				(*this)["Actions"].Get<Scope*>()->Find("Else")->Get<Scope*>()->As<ActionList>()->Update(worldState);
			}
		}
	}
}