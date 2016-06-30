#include "pch.h"
#include "ActionWhile.h"
#include "Sector.h"
#include <sstream>

namespace Library
{
	RTTI_DEFINITIONS(ActionWhile)

		ActionWhile::ActionWhile(const std::string& name)
		: ActionList(name), mActionExpression(nullptr), mConditionDatum(nullptr)
	{
		InternalAttribute(Condition, 1, Datum::INTEGER, nullptr)
		Populate();
	}

	/*
	The end user needs to place, in XML, Actions (or ActionLists) labeled as
	'Then' and 'Else', and then the Update loop for those Actions will occur
	or not occur based on the current state of the condition, mCondition.
	*/
	void ActionWhile::Update(const WorldState& worldState)
	{
		// If 'Condition' is not initialized, the default condition
		// evaluates to false, because it is a nullptr (i.e., 0)
		while(Find("Condition")->Get<int>())
		{
			if (mConditionDatum != nullptr)
			{
				// Need to make sure the Datum is of type <int>
				Find("Condition")->Set(mConditionDatum->Get<int>(0));
			}

			//std::cout << "\nThe condition is currently: " << Find("Condition")->Get<int>() << std::endl;
			ActionList::Update(worldState);

			// If the condition is based on an ActionExpression,
			// then first find it here and then update the
			// ActionExpression and then the condition based on it
			if (Actions()->Find("Expression"))
			{
				mActionExpression = Actions()->Find("Expression")->Get<Scope*>()->As<ActionExpression>();
				Find("Condition")->Set(mActionExpression->GetTarget()->Get<int>(0));
			}
		}
	}
}